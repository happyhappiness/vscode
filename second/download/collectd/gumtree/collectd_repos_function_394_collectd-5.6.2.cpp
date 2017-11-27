static int read_sysfs(void) /* {{{ */
{
  int status;
  int battery_counter = 0;

  if (access(SYSFS_PATH, R_OK) != 0)
    return (ENOENT);

  status = walk_directory(SYSFS_PATH, read_sysfs_callback,
                          /* user_data = */ &battery_counter,
                          /* include hidden */ 0);
  return (status);
}