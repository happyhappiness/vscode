static int read_acpi_callback(char const *dir, /* {{{ */
                              char const *power_supply, void *user_data) {
  int *battery_index = user_data;

  gauge_t power = NAN;
  gauge_t voltage = NAN;
  gauge_t capacity_charged = NAN;
  gauge_t capacity_full = NAN;
  gauge_t capacity_design = NAN;
  _Bool charging = 0;
  _Bool is_current = 0;

  char const *plugin_instance;
  char filename[PATH_MAX];
  char buffer[1024];

  FILE *fh;

  snprintf(filename, sizeof(filename), "%s/%s/state", dir, power_supply);
  fh = fopen(filename, "r");
  if (fh == NULL) {
    if ((errno == EAGAIN) || (errno == EINTR) || (errno == ENOENT))
      return 0;
    else
      return errno;
  }

  /*
   * [11:00] <@tokkee> $ cat /proc/acpi/battery/BAT1/state
   * [11:00] <@tokkee> present:                 yes
   * [11:00] <@tokkee> capacity state:          ok
   * [11:00] <@tokkee> charging state:          charging
   * [11:00] <@tokkee> present rate:            1724 mA
   * [11:00] <@tokkee> remaining capacity:      4136 mAh
   * [11:00] <@tokkee> present voltage:         12428 mV
   */
  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *fields[8];
    int numfields;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields < 3)
      continue;

    if ((strcmp(fields[0], "charging") == 0) &&
        (strcmp(fields[1], "state:") == 0)) {
      if (strcmp(fields[2], "charging") == 0)
        charging = 1;
      else
        charging = 0;
      continue;
    }

    /* The unit of "present rate" depends on the battery. Modern
     * batteries export power (watts), older batteries (used to)
     * export current (amperes). We check the fourth column and try
     * to find old batteries this way. */
    if ((strcmp(fields[0], "present") == 0) &&
        (strcmp(fields[1], "rate:") == 0)) {
      strtogauge(fields[2], &power);

      if ((numfields >= 4) && (strcmp("mA", fields[3]) == 0))
        is_current = 1;
    } else if ((strcmp(fields[0], "remaining") == 0) &&
               (strcmp(fields[1], "capacity:") == 0))
      strtogauge(fields[2], &capacity_charged);
    else if ((strcmp(fields[0], "present") == 0) &&
             (strcmp(fields[1], "voltage:") == 0))
      strtogauge(fields[2], &voltage);
  } /* while (fgets (buffer, sizeof (buffer), fh) != NULL) */

  fclose(fh);

  if (!charging)
    power *= -1.0;

  /* FIXME: This is a dirty hack for backwards compatibility: The battery
   * plugin, for a very long time, has had the plugin_instance
   * hard-coded to "0". So, to keep backwards compatibility, we'll use
   * "0" for the first battery we find and the power_supply name for all
   * following. This should be reverted in a future major version. */
  plugin_instance = (*battery_index == 0) ? "0" : power_supply;
  (*battery_index)++;

  read_acpi_full_capacity(dir, power_supply, &capacity_full, &capacity_design);

  submit_capacity(plugin_instance, capacity_charged * PROC_ACPI_FACTOR,
                  capacity_full * PROC_ACPI_FACTOR,
                  capacity_design * PROC_ACPI_FACTOR);

  battery_submit(plugin_instance, is_current ? "current" : "power",
                 power * PROC_ACPI_FACTOR);
  battery_submit(plugin_instance, "voltage", voltage * PROC_ACPI_FACTOR);

  return 0;
}