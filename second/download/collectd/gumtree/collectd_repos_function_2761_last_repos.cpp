static int cf_dispatch(const char *type, const char *orig_key,
                       const char *orig_value) {
  cf_callback_t *cf_cb;
  plugin_ctx_t old_ctx;
  char *key;
  char *value;
  int ret;
  int i = 0;

  if (orig_key == NULL)
    return EINVAL;

  DEBUG("type = %s, key = %s, value = %s", ESCAPE_NULL(type), orig_key,
        ESCAPE_NULL(orig_value));

  if ((cf_cb = cf_search(type)) == NULL) {
    WARNING("Found a configuration for the `%s' plugin, but "
            "the plugin isn't loaded or didn't register "
            "a configuration callback.",
            type);
    return -1;
  }

  if ((key = strdup(orig_key)) == NULL)
    return 1;
  if ((value = strdup(orig_value)) == NULL) {
    free(key);
    return 2;
  }

  ret = -1;

  old_ctx = plugin_set_ctx(cf_cb->ctx);

  for (i = 0; i < cf_cb->keys_num; i++) {
    if ((cf_cb->keys[i] != NULL) && (strcasecmp(cf_cb->keys[i], key) == 0)) {
      ret = (*cf_cb->callback)(key, value);
      break;
    }
  }

  plugin_set_ctx(old_ctx);

  if (i >= cf_cb->keys_num)
    WARNING("Plugin `%s' did not register for value `%s'.", type, key);

  free(key);
  free(value);

  return ret;
}