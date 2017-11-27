static int lv_shutdown(void) {
  for (int i = 0; i < nr_instances; ++i) {
    lv_fini_instance(i);
  }

  lv_disconnect();

  ignorelist_free(il_domains);
  il_domains = NULL;
  ignorelist_free(il_block_devices);
  il_block_devices = NULL;
  ignorelist_free(il_interface_devices);
  il_interface_devices = NULL;

  return 0;
}