int plugin_register_config(const char *name,
                           int (*callback)(const char *key, const char *val),
                           const char **keys, int keys_num) {
  return ENOTSUP;
}