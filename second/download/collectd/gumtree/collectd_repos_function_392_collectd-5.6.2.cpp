static int read_sysfs_capacity(char const *dir, /* {{{ */
                               char const *power_supply,
                               char const *plugin_instance) {
  gauge_t capacity_charged = NAN;
  gauge_t capacity_full = NAN;
  gauge_t capacity_design = NAN;
  int status;

  status =
      sysfs_file_to_gauge(dir, power_supply, "energy_now", &capacity_charged);
  if (status != 0)
    return (status);

  status =
      sysfs_file_to_gauge(dir, power_supply, "energy_full", &capacity_full);
  if (status != 0)
    return (status);

  status = sysfs_file_to_gauge(dir, power_supply, "energy_full_design",
                               &capacity_design);
  if (status != 0)
    return (status);

  submit_capacity(plugin_instance, capacity_charged * SYSFS_FACTOR,
                  capacity_full * SYSFS_FACTOR, capacity_design * SYSFS_FACTOR);
  return (0);
}