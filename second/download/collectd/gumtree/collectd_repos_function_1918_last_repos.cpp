void module_register(void) {
  plugin_register_init("lvm", c_lvm_init);
  plugin_register_read("lvm", lvm_read);
}