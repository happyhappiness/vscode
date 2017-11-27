static int read_pmu(void) /* {{{ */
{
  int i = 0;
  /* The upper limit here is just a safeguard. If there is a system with
   * more than 100 batteries, this can easily be increased. */
  for (; i < 100; i++) {
    FILE *fh;

    char buffer[1024];
    char filename[PATH_MAX];
    char plugin_instance[DATA_MAX_NAME_LEN];

    gauge_t current = NAN;
    gauge_t voltage = NAN;
    gauge_t charge = NAN;

    ssnprintf(filename, sizeof(filename), PROC_PMU_PATH_FORMAT, i);
    if (access(filename, R_OK) != 0)
      break;

    ssnprintf(plugin_instance, sizeof(plugin_instance), "%i", i);

    fh = fopen(filename, "r");
    if (fh == NULL) {
      if (errno == ENOENT)
        break;
      else if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      else
        return (errno);
    }

    while (fgets(buffer, sizeof(buffer), fh) != NULL) {
      char *fields[8];
      int numfields;

      numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
      if (numfields < 3)
        continue;

      if (strcmp("current", fields[0]) == 0)
        strtogauge(fields[2], &current);
      else if (strcmp("voltage", fields[0]) == 0)
        strtogauge(fields[2], &voltage);
      else if (strcmp("charge", fields[0]) == 0)
        strtogauge(fields[2], &charge);
    }

    fclose(fh);
    fh = NULL;

    battery_submit(plugin_instance, "charge", charge / 1000.0);
    battery_submit(plugin_instance, "current", current / 1000.0);
    battery_submit(plugin_instance, "voltage", voltage / 1000.0);
  }

  if (i == 0)
    return (ENOENT);
  return (0);
}