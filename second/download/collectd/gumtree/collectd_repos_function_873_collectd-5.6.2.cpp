static int ethstat_shutdown(void) {
  void *key = NULL;
  void *value = NULL;

  if (value_map == NULL)
    return (0);

  while (c_avl_pick(value_map, &key, &value) == 0) {
    sfree(key);
    sfree(value);
  }

  c_avl_destroy(value_map);
  value_map = NULL;

  return (0);
}