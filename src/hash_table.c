#include "hash_table.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t entry_count = 0;
static entry_t map[MAP_CAP];

uint64_t fnv1a(const char *s, int len) {
  uint64_t h = 0xcbf29ce484222325ULL;
  for (int i = 0; i < len; i++) {
    h ^= (uint8_t)s[i];
    h *= 1099511628211ULL;
  }
  return h;
}

entry_t *lookup_or_insert(const char *name, int len, uint64_t hash) {
  size_t i = (size_t)hash & (MAP_CAP - 1);
  for (;;) {
    entry_t *e = &map[i];
    if (!e->used) {
      e->used = 1;
      e->name_len = len;
      memcpy(e->name, name, (size_t)len);
      e->name[len] = '\0';
      e->hash = hash;
      e->min = INT32_MAX;
      e->max = INT32_MIN;
      e->sum = 0;
      e->count = 0;
      entry_count++;
      return e;
    }
    if (e->name_len == len && e->hash == hash) {
      return e;
    }
    i = (i + 1) & (MAP_CAP - 1);
  }
}

static void update_min_max(entry_t *e, int32_t temp) {
  if (temp < e->min)
    e->min = temp;
  if (temp > e->max)
    e->max = temp;
}

void update_entry(entry_t *e, int32_t temp) {
  update_min_max(e, temp);
  e->sum += temp;
  e->count++;
}

uint8_t to_list(entry_list_t *el) {
  entry_t **list = malloc(sizeof *list * (size_t)entry_count);

  if (!list) {
    return 1;
  }
  int n = 0;
  for (size_t i = 0; i < MAP_CAP; i++) {
    if (map[i].used) {
      list[n++] = &map[i];
    }
  }
  el->list = list;
  el->size = n;
  return 0;
}
