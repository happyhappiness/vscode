void module_register(void) {
  plugin_register_init("ipvs", cipvs_init);
  plugin_register_read("ipvs", cipvs_read);
  plugin_register_shutdown("ipvs", cipvs_shutdown);
  return;
}