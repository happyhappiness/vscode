static int swap_read_io(void) /* {{{ */
{
  FILE *fh;
  char buffer[1024];

  _Bool old_kernel = 0;

  uint8_t have_data = 0;
  derive_t swap_in = 0;
  derive_t swap_out = 0;

  fh = fopen("/proc/vmstat", "r");
  if (fh == NULL) {
    /* /proc/vmstat does not exist in kernels <2.6 */
    fh = fopen("/proc/stat", "r");
    if (fh == NULL) {
      char errbuf[1024];
      WARNING("swap: fopen: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
      return (-1);
    } else
      old_kernel = 1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *fields[8];
    int numfields;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));

    if (!old_kernel) {
      if (numfields != 2)
        continue;

      if (strcasecmp("pswpin", fields[0]) == 0) {
        strtoderive(fields[1], &swap_in);
        have_data |= 0x01;
      } else if (strcasecmp("pswpout", fields[0]) == 0) {
        strtoderive(fields[1], &swap_out);
        have_data |= 0x02;
      }
    } else /* if (old_kernel) */
    {
      if (numfields != 3)
        continue;

      if (strcasecmp("page", fields[0]) == 0) {
        strtoderive(fields[1], &swap_in);
        strtoderive(fields[2], &swap_out);
      }
    }
  } /* while (fgets) */

  fclose(fh);

  if (have_data != 0x03)
    return (ENOENT);

  if (report_bytes) {
    swap_in = swap_in * pagesize;
    swap_out = swap_out * pagesize;
  }

  swap_submit_derive("in", swap_in);
  swap_submit_derive("out", swap_out);

  return (0);
}