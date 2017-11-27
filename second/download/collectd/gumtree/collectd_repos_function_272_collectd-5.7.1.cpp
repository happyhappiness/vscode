static int irq_read(void) {
  FILE *fh;
  char buffer[1024];
  int cpu_count;
  char *fields[256];

  /*
   * Example content:
   *         CPU0       CPU1       CPU2       CPU3
   * 0:       2574          1          3          2   IO-APIC-edge      timer
   * 1:     102553     158669     218062      70587   IO-APIC-edge      i8042
   * 8:          0          0          0          1   IO-APIC-edge      rtc0
   */
  fh = fopen("/proc/interrupts", "r");
  if (fh == NULL) {
    char errbuf[1024];
    ERROR("irq plugin: fopen (/proc/interrupts): %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  /* Get CPU count from the first line */
  if (fgets(buffer, sizeof(buffer), fh) != NULL) {
    cpu_count = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
  } else {
    ERROR("irq plugin: unable to get CPU count from first line "
          "of /proc/interrupts");
    fclose(fh);
    return (-1);
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *irq_name;
    size_t irq_name_len;
    derive_t irq_value;
    int i;
    int fields_num;
    int irq_values_to_parse;

    fields_num = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (fields_num < 2)
      continue;

    /* Parse this many numeric fields, skip the rest
     * (+1 because first there is a name of irq in each line) */
    if (fields_num >= cpu_count + 1)
      irq_values_to_parse = cpu_count;
    else
      irq_values_to_parse = fields_num - 1;

    /* First field is irq name and colon */
    irq_name = fields[0];
    irq_name_len = strlen(irq_name);
    if (irq_name_len < 2)
      continue;

    /* Check if irq name ends with colon.
     * Otherwise it's a header. */
    if (irq_name[irq_name_len - 1] != ':')
      continue;

    /* Is it the the ARM fast interrupt (FIQ)? */
    if (irq_name_len == 4 && (strncmp(irq_name, "FIQ:", 4) == 0))
      continue;

    irq_name[irq_name_len - 1] = 0;
    irq_name_len--;

    irq_value = 0;
    for (i = 1; i <= irq_values_to_parse; i++) {
      /* Per-CPU value */
      value_t v;
      int status;

      status = parse_value(fields[i], &v, DS_TYPE_DERIVE);
      if (status != 0)
        break;

      irq_value += v.derive;
    } /* for (i) */

    /* No valid fields -> do not submit anything. */
    if (i <= 1)
      continue;

    irq_submit(irq_name, irq_value);
  }

  fclose(fh);

  return (0);
}