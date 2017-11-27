static int serial_read(void) {
  FILE *fh;
  char buffer[1024];

  /* there are a variety of names for the serial device */
  if ((fh = fopen("/proc/tty/driver/serial", "r")) == NULL &&
      (fh = fopen("/proc/tty/driver/ttyS", "r")) == NULL) {
    char errbuf[1024];
    WARNING("serial: fopen: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    derive_t rx = 0;
    derive_t tx = 0;
    _Bool have_rx = 0, have_tx = 0;
    size_t len;

    char *fields[16];
    int numfields;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields < 6)
      continue;

    /*
     * 0: uart:16550A port:000003F8 irq:4 tx:0 rx:0
     * 1: uart:16550A port:000002F8 irq:3 tx:0 rx:0
     */
    len = strlen(fields[0]);
    if (len < 2)
      continue;
    if (fields[0][len - 1] != ':')
      continue;
    fields[0][len - 1] = 0;

    for (int i = 1; i < numfields; i++) {
      len = strlen(fields[i]);
      if (len < 4)
        continue;

      if (strncmp(fields[i], "tx:", 3) == 0) {
        if (strtoderive(fields[i] + 3, &tx) == 0)
          have_tx = 1;
      } else if (strncmp(fields[i], "rx:", 3) == 0) {
        if (strtoderive(fields[i] + 3, &rx) == 0)
          have_rx = 1;
      }
    }

    if (have_rx && have_tx)
      serial_submit(fields[0], rx, tx);
  }

  fclose(fh);
  return (0);
}