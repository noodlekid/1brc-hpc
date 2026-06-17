#include "parsing.h"
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
