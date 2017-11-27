static int read_sysfs_callback(char const *dir, /* {{{ */
                               char const *power_supply, void *user_data) {
  int *battery_index = user_data;

  char const *plugin_instance;
  char buffer[32];
  gauge_t v = NAN;
  _Bool discharging = 0;
  int status;

  /* Ignore non-battery directories, such as AC power. */
  status =
      sysfs_file_to_buffer(dir, power_supply, "type", buffer, sizeof(buffer));
  if (status != 0)
    return (0);
  if (strcasecmp("Battery", buffer) != 0)
    return (0);

  (void)sysfs_file_to_buffer(dir, power_supply, "status", buffer,
                             sizeof(buffer));
  if (strcasecmp("Discharging", buffer) == 0)
    discharging = 1;

  /* FIXME: This is a dirty hack for backwards compatibility: The battery
   * plugin, for a very long time, has had the plugin_instance
   * hard-coded to "0". So, to keep backwards compatibility, we'll use
   * "0" for the first battery we find and the power_supply name for all
   * following. This should be reverted in a future major version. */
  plugin_instance = (*battery_index == 0) ? "0" : power_supply;
  (*battery_index)++;

  read_sysfs_capacity(dir, power_supply, plugin_instance);

  if (sysfs_file_to_gauge(dir, power_supply, "power_now", &v) == 0) {
    if (discharging)
      v *= -1.0;
    battery_submit(plugin_instance, "power", v * SYSFS_FACTOR);
  }
  if (sysfs_file_to_gauge(dir, power_supply, "current_now", &v) == 0) {
    if (discharging)
      v *= -1.0;
    battery_submit(plugin_instance, "current", v * SYSFS_FACTOR);
  }

  if (sysfs_file_to_gauge(dir, power_supply, "voltage_now", &v) == 0)
    battery_submit(plugin_instance, "voltage", v * SYSFS_FACTOR);

  return (0);
}