static int format_rfc3339(char *buffer, size_t buffer_size, cdtime_t t,
                          _Bool print_nano) /* {{{ */
{
  struct timespec t_spec;
  struct tm t_tm;
  char base[20]; /* 2006-01-02T15:04:05 */
  char nano[11]; /* .999999999 */
  char zone[7];  /* +00:00 */
  char *fields[] = {base, nano, zone};
  size_t len;
  int status;

  CDTIME_T_TO_TIMESPEC(t, &t_spec);
  NORMALIZE_TIMESPEC(t_spec);

  if (localtime_r(&t_spec.tv_sec, &t_tm) == NULL) {
    char errbuf[1024];
    status = errno;
    ERROR("format_rfc3339: localtime_r failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    return (status);
  }

  len = strftime(base, sizeof(base), "%Y-%m-%dT%H:%M:%S", &t_tm);
  if (len == 0)
    return ENOMEM;

  if (print_nano)
    ssnprintf(nano, sizeof(nano), ".%09ld", (long)t_spec.tv_nsec);
  else
    sstrncpy(nano, "", sizeof(nano));

  status = format_zone(zone, sizeof(zone), &t_tm);
  if (status != 0)
    return status;

  if (strjoin(buffer, buffer_size, fields, STATIC_ARRAY_SIZE(fields), "") < 0)
    return ENOMEM;
  return 0;
}