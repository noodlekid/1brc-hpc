#ifndef PARSING_H
#define PARSING_H

#include <stdint.h>

typedef struct {
  int name_len;
  int temp_len;
  char *semi;
} line_info_t;

int32_t parse_tenths(const char *s, int len);
void parse_line(char *line, line_info_t *line_i);

#endif // !PARSING_H
