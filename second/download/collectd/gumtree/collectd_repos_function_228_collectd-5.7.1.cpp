static void free_block_devices(void) {
  if (block_devices) {
    for (int i = 0; i < nr_block_devices; ++i)
      sfree(block_devices[i].path);
    sfree(block_devices);
  }
  block_devices = NULL;
  nr_block_devices = 0;
}