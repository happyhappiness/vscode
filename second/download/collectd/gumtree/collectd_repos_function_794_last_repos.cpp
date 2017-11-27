static int fc_init(void) {
  if (directories_num < 1) {
    WARNING("filecount plugin: No directories have been configured.");
    return -1;
  }

  return 0;
}