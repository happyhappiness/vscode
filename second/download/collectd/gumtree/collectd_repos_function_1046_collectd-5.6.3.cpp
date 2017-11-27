void module_register(void) {
  plugin_register_init("vserver", vserver_init);
  plugin_register_read("vserver", vserver_read);
}