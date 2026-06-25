#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define MAP_CAP (1u << 14)
#define MAX_NAME 128

typedef struct {
  uint64_t hash;
  int64_t sum; /* tenths */
  int64_t count;
  int32_t min; /* tenths of a degree */
  int32_t max; /* tenths */
  char* name; /* pointer to name in mmap buffer */
  uint8_t used;
  uint8_t name_len;
} entry_t;


typedef struct {
  size_t size;
  entry_t **list;
} entry_list_t;

entry_t *lookup_or_insert(const char *name, int len, uint64_t hash);
uint64_t fnv1a(const char *s, int len);
void update_entry(entry_t *e, int32_t temp);
uint8_t to_list(entry_list_t *el);

#endif // !HASH_TABLE_H
