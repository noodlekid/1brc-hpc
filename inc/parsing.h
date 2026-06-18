#ifndef PARSING_H
#define PARSING_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  int name_len;
  int temp_len;
  char *semi;
} line_info_t;

int32_t parse_tenths(const char *s, int len);
void parse_line(char *line, line_info_t *line_i);
void parse_line_fast(char *start, char *end, line_info_t *line_i);
const char *find_newline_avx2(const char *data, size_t length);

#endif // !PARSING_H
