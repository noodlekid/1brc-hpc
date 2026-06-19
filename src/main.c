#define _POSIX_C_SOURCE 200809L
#include "hash_table.h"
#include "parsing.h"
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LINE_BUF (MAX_NAME + 16)

extern uint32_t entry_count;

static int cmp_entry(const void *pa, const void *pb) {
  const entry_t *a = *(entry_t *const *)pa;
  const entry_t *b = *(entry_t *const *)pb;
  return strcmp(a->name, b->name);
}

/* Java's Math.round: half-up toward +infinity. */
static double round_java(double x) { return floor(x + 0.5); }

/* Format a value given in tenths-units, rounded to one decimal. */
static void format_tenths(char *buf, size_t buflen, double tenths_val) {
  double r = round_java(tenths_val) / 10.0;
  if (r == 0.0)
    r = 0.0; /* normalize -0.0 to +0.0 just in case */
  snprintf(buf, buflen, "%.1f", r);
}

int main(int argc, char **argv) {
  const char *fname = argc > 1 ? argv[1] : "measurements.txt";
  int fp = open(fname, O_RDONLY);
  if (fp < 0) {
    perror(fname);
    return 1;
  }

  line_info_t line_info;

  //---
  char *lines;
  struct stat buffer;
  fstat(fp, &buffer);
  lines = (char *)mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, fp, 0);
  close(fp);
  char *p = lines;
  char *end = lines + buffer.st_size;

  while (p < end) {
    // 1. Calculate strictly remaining bytes to prevent SIMD out-of-bounds reads
    size_t remaining = end - p;

    // 2. Find the newline character
    const char *n = find_newline_avx2(p, remaining);

    // 3. Handle edge case: File does not end in a newline
    if (n == NULL) {
      n = end;
    }

    // 4. Parse the bounds of the line
    parse_line_fast(p, (char *)n, &line_info);

    // 5. Extract values and update the hash table
    int32_t t = parse_tenths_fast(line_info.semi + 1, line_info.temp_len);
    entry_t *e =
        lookup_or_insert(p, line_info.name_len, fnv1a(p, line_info.name_len));
    update_entry(e, t);

    // 6. Advance 'p' past the newline character to begin the next line
    p = (char *)n + 1;
  }

  entry_list_t el;
  to_list(&el);
  qsort(el.list, el.size, sizeof *el.list, cmp_entry);

  // output -------------------------------------------------------------
  fputc('{', stdout);
  for (size_t i = 0; i < el.size; i++) {
    entry_t *e = el.list[i];
    char mins[16], means[16], maxs[16];
    format_tenths(mins, sizeof mins, (double)e->min);
    format_tenths(means, sizeof means, (double)e->sum / (double)e->count);
    format_tenths(maxs, sizeof maxs, (double)e->max);
    if (i > 0)
      fputs(", ", stdout);
    printf("%s=%s/%s/%s", e->name, mins, means, maxs);
  }
  fputs("}\n", stdout);
  // output -------------------------------------------------------------

  free(el.list);
  return 0;
}
