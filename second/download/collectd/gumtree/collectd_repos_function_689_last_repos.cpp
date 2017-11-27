static int ps_read_io(process_entry_t *ps) {
  FILE *fh;
  char buffer[1024];
  char filename[64];

  char *fields[8];
  int numfields;

  snprintf(filename, sizeof(filename), "/proc/%li/io", ps->id);
  if ((fh = fopen(filename, "r")) == NULL) {
    DEBUG("ps_read_io: Failed to open file `%s'", filename);
    return -1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    derive_t *val = NULL;
    long long tmp;
    char *endptr;

    if (strncasecmp(buffer, "rchar:", 6) == 0)
      val = &(ps->io_rchar);
    else if (strncasecmp(buffer, "wchar:", 6) == 0)
      val = &(ps->io_wchar);
    else if (strncasecmp(buffer, "syscr:", 6) == 0)
      val = &(ps->io_syscr);
    else if (strncasecmp(buffer, "syscw:", 6) == 0)
      val = &(ps->io_syscw);
    else if (strncasecmp(buffer, "read_bytes:", 11) == 0)
      val = &(ps->io_diskr);
    else if (strncasecmp(buffer, "write_bytes:", 12) == 0)
      val = &(ps->io_diskw);
    else
      continue;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));

    if (numfields < 2)
      continue;

    errno = 0;
    endptr = NULL;
    tmp = strtoll(fields[1], &endptr, /* base = */ 10);
    if ((errno != 0) || (endptr == fields[1]))
      *val = -1;
    else
      *val = (derive_t)tmp;
  } /* while (fgets) */

  if (fclose(fh)) {
    char errbuf[1024];
    WARNING("processes: fclose: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
  }
  return 0;
}