static int swap_read_separate(void) /* {{{ */
{
  FILE *fh;
  char buffer[1024];

  fh = fopen("/proc/swaps", "r");
  if (fh == NULL) {
    char errbuf[1024];
    WARNING("swap plugin: fopen (/proc/swaps) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *fields[8];
    int numfields;
    char *endptr;

    char path[PATH_MAX];
    gauge_t total;
    gauge_t used;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields != 5)
      continue;

    sstrncpy(path, fields[0], sizeof(path));
    escape_slashes(path, sizeof(path));

    errno = 0;
    endptr = NULL;
    total = strtod(fields[2], &endptr);
    if ((endptr == fields[2]) || (errno != 0))
      continue;

    errno = 0;
    endptr = NULL;
    used = strtod(fields[3], &endptr);
    if ((endptr == fields[3]) || (errno != 0))
      continue;

    if (total < used)
      continue;

    swap_submit_usage(path, used * 1024.0, (total - used) * 1024.0, NULL, NAN);
  }

  fclose(fh);

  return 0;
}