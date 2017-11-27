void module_register(void) {
  plugin_register_complex_config("dpdkstat", dpdk_config);
  plugin_register_init("dpdkstat", dpdk_init);
  plugin_register_complex_read(NULL, "dpdkstat", dpdk_read, 0, NULL);
  plugin_register_shutdown("dpdkstat", dpdk_shutdown);
}