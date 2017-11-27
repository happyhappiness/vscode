void module_register(void) {
  plugin_register_init("drbd", drbd_init);
  plugin_register_read("drbd", drbd_read);
}