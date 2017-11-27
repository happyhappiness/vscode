static int procfs_iterate(int sk) {
  char buffer[1024];
  char *device, *dummy;
  FILE *fh;
  int status;
  int num_success;
  int num_fail;

  if ((fh = fopen("/proc/net/dev", "r")) == NULL) {
    WARNING("madwifi plugin: opening /proc/net/dev failed");
    return -1;
  }

  num_success = 0;
  num_fail = 0;
  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    dummy = strchr(buffer, ':');
    if (dummy == NULL)
      continue;
    dummy[0] = 0;

    device = buffer;
    while (device[0] == ' ')
      device++;

    if (device[0] == 0)
      continue;

    if (ignorelist_match(ignorelist, device) != 0)
      continue;

    status = process_device(sk, device);
    if (status != 0) {
      ERROR("madwifi plugin: Processing interface "
            "%s failed.",
            device);
      num_fail++;
    } else {
      num_success++;
    }
  } /* while (fgets) */

  fclose(fh);

  if ((num_success == 0) && (num_fail != 0))
    return -1;
  return 0;
}