static int sysfs_iterate(int sk) {
  struct dirent *de;
  DIR *nets;
  int status;
  int num_success;
  int num_fail;

  nets = opendir("/sys/class/net/");
  if (nets == NULL) {
    WARNING("madwifi plugin: opening /sys/class/net failed");
    return (-1);
  }

  num_success = 0;
  num_fail = 0;
  while ((de = readdir(nets))) {
    if (check_devname(de->d_name) == 0)
      continue;

    if (ignorelist_match(ignorelist, de->d_name) != 0)
      continue;

    status = process_device(sk, de->d_name);
    if (status != 0) {
      ERROR("madwifi plugin: Processing interface "
            "%s failed.",
            de->d_name);
      num_fail++;
    } else {
      num_success++;
    }
  } /* while (readdir) */

  closedir(nets);

  if ((num_success == 0) && (num_fail != 0))
    return (-1);
  return (0);
}