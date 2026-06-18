#include "parsing.h"
#include <immintrin.h> // Required for AVX2 intrinsics
#include <stddef.h>    // Required for size_t
#include <string.h>

int32_t parse_tenths(const char *s, int len) {
  int neg = 0;
  int i = 0;
  if (s[0] == '-') {
    neg = 1;
    i = 1;
  }
  int32_t v;
  if (len - i == 3) {
    /* d.d */
    v = (s[i] - '0') * 10 + (s[i + 2] - '0');
  } else {
    /* dd.d */
    v = (s[i] - '0') * 100 + (s[i + 1] - '0') * 10 + (s[i + 3] - '0');
  }
  return neg ? -v : v;
}

void parse_line(char *line, line_info_t *line_i) {
  int len = (int)strlen(line);
  while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
    line[--len] = '\0';
  }
  char *semi = memchr(line, ';', (size_t)len);
  line_i->semi = semi;
  line_i->name_len = (int)(semi - line);
  line_i->temp_len = len - line_i->name_len - 1;
}

void parse_line_fast(char *start, char *end, line_info_t *line_i) {
  int len = end - start;
  char *semi = memchr(start, ';', len);
  line_i->semi = semi;
  line_i->name_len = semi - start;
  line_i->temp_len = len - line_i->name_len - 1;
}

const char *find_newline_avx2(const char *data, size_t length) {
  if (length == 0 || data == NULL)
    return NULL;

  __m256i nl_vec = _mm256_set1_epi8('\n');

  size_t i = 0;

  for (; i + 32 <= length; i += 32) {
    __m256i chunk = _mm256_loadu_si256((const __m256i *)(data + i));
    __m256i cmp = _mm256_cmpeq_epi8(chunk, nl_vec);

    int mask = _mm256_movemask_epi8(cmp);

    if (mask != 0) {
      int match_idx = __builtin_ctz(mask);
      return data + i + match_idx;
    }
  }

  for (; i < length; ++i) {
    if (data[i] == '\n') {
      return data + i;
    }
  }

  return NULL;
}
