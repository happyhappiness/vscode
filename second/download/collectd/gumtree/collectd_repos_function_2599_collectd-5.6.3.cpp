int plugin_register_complex_config(const char *type,
                                   int (*callback)(oconfig_item_t *)) {
  return (cf_register_complex(type, callback));
}