void module_register(void) {
  plugin_register_read("lvm", lvm_read);
}