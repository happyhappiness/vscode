static int sysfs_file_to_gauge(char const *dir, /* {{{ */
                               char const *power_supply, char const *basename,
                               gauge_t *ret_value) {
  int status;
  char buffer[32] = "";

  status =
      sysfs_file_to_buffer(dir, power_supply, basename, buffer, sizeof(buffer));
  if (status != 0)
    return (status);

  return (strtogauge(buffer, ret_value));
}