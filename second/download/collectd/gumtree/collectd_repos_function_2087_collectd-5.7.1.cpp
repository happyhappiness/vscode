void module_register(void) {
  plugin_register_complex_config("memcachec", cmc_config);
  plugin_register_init("memcachec", cmc_init);
  plugin_register_read("memcachec", cmc_read);
  plugin_register_shutdown("memcachec", cmc_shutdown);
}