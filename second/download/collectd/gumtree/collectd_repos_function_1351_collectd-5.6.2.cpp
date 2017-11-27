static int swap_read_combined(void) /* {{{ */
{
  FILE *fh;
  char buffer[1024];

  gauge_t swap_used = NAN;
  gauge_t swap_cached = NAN;
  gauge_t swap_free = NAN;
  gauge_t swap_total = NAN;

  fh = fopen("/proc/meminfo", "r");
  if (fh == NULL) {
    char errbuf[1024];
    WARNING("swap plugin: fopen (/proc/meminfo) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *fields[8];
    int numfields;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields < 2)
      continue;

    if (strcasecmp(fields[0], "SwapTotal:") == 0)
      strtogauge(fields[1], &swap_total);
    else if (strcasecmp(fields[0], "SwapFree:") == 0)
      strtogauge(fields[1], &swap_free);
    else if (strcasecmp(fields[0], "SwapCached:") == 0)
      strtogauge(fields[1], &swap_cached);
  }

  fclose(fh);

  if (isnan(swap_total) || isnan(swap_free))
    return (ENOENT);

  /* Some systems, OpenVZ for example, don't provide SwapCached. */
  if (isnan(swap_cached))
    swap_used = swap_total - swap_free;
  else
    swap_used = swap_total - (swap_free + swap_cached);
  assert(!isnan(swap_used));

  if (swap_used < 0.0)
    return (EINVAL);

  swap_submit_usage(NULL, swap_used * 1024.0, swap_free * 1024.0,
                    isnan(swap_cached) ? NULL : "cached",
                    isnan(swap_cached) ? NAN : swap_cached * 1024.0);
  return (0);
}