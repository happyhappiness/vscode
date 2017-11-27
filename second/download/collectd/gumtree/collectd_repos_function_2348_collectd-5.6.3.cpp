static cache_entry_t *cache_alloc(size_t values_num) {
  cache_entry_t *ce;

  ce = calloc(1, sizeof(*ce));
  if (ce == NULL) {
    ERROR("utils_cache: cache_alloc: calloc failed.");
    return (NULL);
  }
  ce->values_num = values_num;

  ce->values_gauge = calloc(values_num, sizeof(*ce->values_gauge));
  ce->values_raw = calloc(values_num, sizeof(*ce->values_raw));
  if ((ce->values_gauge == NULL) || (ce->values_raw == NULL)) {
    sfree(ce->values_gauge);
    sfree(ce->values_raw);
    sfree(ce);
    ERROR("utils_cache: cache_alloc: calloc failed.");
    return (NULL);
  }

  ce->history = NULL;
  ce->history_length = 0;
  ce->meta = NULL;

  return (ce);
}