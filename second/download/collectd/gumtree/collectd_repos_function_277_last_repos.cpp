static int thermal_procfs_read(void) {
  return walk_directory(dirname_procfs, thermal_procfs_device_read, NULL, 0);
}