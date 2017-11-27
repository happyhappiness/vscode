int plugin_unregister_complex_config(const char *name) {
  cf_unregister_complex(name);
  return (0);
}