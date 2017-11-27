static int hddtemp_read(void) {
  char *buf;
  char *ptr;
  char *saveptr;
  char *name;
  char *model;
  char *temperature;
  char *mode;

  /* get data from daemon */
  buf = hddtemp_query_daemon();
  if (buf == NULL)
    return (-1);

  /* NB: strtok_r will eat up "||" and leading "|"'s */
  ptr = buf;
  saveptr = NULL;
  while ((name = strtok_r(ptr, "|", &saveptr)) != NULL &&
         (model = strtok_r(NULL, "|", &saveptr)) != NULL &&
         (temperature = strtok_r(NULL, "|", &saveptr)) != NULL &&
         (mode = strtok_r(NULL, "|", &saveptr)) != NULL) {
    double temperature_value;

    ptr = NULL;

    /* Skip non-temperature information */
    if (mode[0] != 'C' && mode[0] != 'F')
      continue;

    name = basename(name);
    temperature_value = atof(temperature);

    /* Convert farenheit to celsius */
    if (mode[0] == 'F')
      temperature_value = (temperature_value - 32.0) * 5.0 / 9.0;

    hddtemp_submit(name, temperature_value);
  }

  free(buf);
  return (0);
}