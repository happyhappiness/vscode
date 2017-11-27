static int thermal_init(void) {
  int ret = -1;

  if (!force_procfs && access(dirname_sysfs, R_OK | X_OK) == 0) {
    ret = plugin_register_read("thermal", thermal_sysfs_read);
  } else if (access(dirname_procfs, R_OK | X_OK) == 0) {
    ret = plugin_register_read("thermal", thermal_procfs_read);
  }

  return ret;
}