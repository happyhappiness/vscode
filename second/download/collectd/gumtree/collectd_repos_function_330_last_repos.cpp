static int read_acpi_full_capacity(char const *dir, /* {{{ */
                                   char const *power_supply,
                                   gauge_t *ret_capacity_full,
                                   gauge_t *ret_capacity_design)

{
  char filename[PATH_MAX];
  char buffer[1024];

  FILE *fh;

  snprintf(filename, sizeof(filename), "%s/%s/info", dir, power_supply);
  fh = fopen(filename, "r");
  if (fh == NULL)
    return errno;

  /* last full capacity:      40090 mWh */
  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    gauge_t *value_ptr;
    int fields_num;
    char *fields[8];
    int index;

    if (strncmp("last full capacity:", buffer, strlen("last full capacity:")) ==
        0) {
      value_ptr = ret_capacity_full;
      index = 3;
    } else if (strncmp("design capacity:", buffer,
                       strlen("design capacity:")) == 0) {
      value_ptr = ret_capacity_design;
      index = 2;
    } else {
      continue;
    }

    fields_num = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (fields_num <= index)
      continue;

    strtogauge(fields[index], value_ptr);
  }

  fclose(fh);
  return 0;
}