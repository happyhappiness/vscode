void module_register() {
  plugin_register_complex_config("write_prometheus", prom_config);
  plugin_register_init("write_prometheus", prom_init);
  plugin_register_write("write_prometheus", prom_write,
                        /* user data = */ NULL);
  plugin_register_missing("write_prometheus", prom_missing,
                          /* user data = */ NULL);
  plugin_register_shutdown("write_prometheus", prom_shutdown);
}