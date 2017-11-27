static void free_interface_devices(void) {
  if (interface_devices) {
    for (int i = 0; i < nr_interface_devices; ++i) {
      sfree(interface_devices[i].path);
      sfree(interface_devices[i].address);
      sfree(interface_devices[i].number);
    }
    sfree(interface_devices);
  }
  interface_devices = NULL;
  nr_interface_devices = 0;
}