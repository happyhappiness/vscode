static int cow_init(void) {
  int status;
  char errbuf[1024];

  if (device_g == NULL) {
    ERROR("onewire plugin: cow_init: No device configured.");
    return -1;
  }

  DEBUG("onewire plugin: about to init device <%s>.", device_g);
  status = (int)OW_init(device_g);
  if (status != 0) {
    ERROR("onewire plugin: OW_init(%s) failed: %s.", device_g,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  plugin_register_complex_read(/* group = */ NULL, "onewire", cow_read,
                               ow_interval, /* user data = */ NULL);
  plugin_register_shutdown("onewire", cow_shutdown);

  return 0;
}