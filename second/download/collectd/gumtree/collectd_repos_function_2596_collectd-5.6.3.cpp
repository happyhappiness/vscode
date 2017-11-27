static void plugin_free_loaded(void) {
  void *key;
  void *value;

  if (plugins_loaded == NULL)
    return;

  while (c_avl_pick(plugins_loaded, &key, &value) == 0) {
    sfree(key);
    assert(value == NULL);
  }

  c_avl_destroy(plugins_loaded);
  plugins_loaded = NULL;
}