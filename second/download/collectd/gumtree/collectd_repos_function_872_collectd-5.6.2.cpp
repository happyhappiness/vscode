static int ethstat_read(void) {
  for (size_t i = 0; i < interfaces_num; i++)
    ethstat_read_interface(interfaces[i]);

  return 0;
}