size_t cdtime_to_iso8601 (char *s, size_t max, cdtime_t t) /* {{{ */
{
  struct timespec t_spec;
  struct tm t_tm;

  size_t len;

  CDTIME_T_TO_TIMESPEC (t, &t_spec);
  NORMALIZE_TIMESPEC (t_spec);

  if (localtime_r ((time_t *)&t_spec.tv_sec, &t_tm) == NULL) {
    char errbuf[1024];
    ERROR ("cdtime_to_iso8601: localtime_r failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (0);
  }

  len = strftime (s, max, "%Y-%m-%dT%H:%M:%S", &t_tm);
  if (len == 0)
    return 0;

  if (max - len > 2) {
    int n = snprintf (s + len, max - len, ".%09i", (int)t_spec.tv_nsec);
    len += (n < max - len) ? n : max - len;
  }

  if (max - len > 3) {
    int n = strftime (s + len, max - len, "%z", &t_tm);
    len += (n < max - len) ? n : max - len;
  }

  s[max - 1] = '\0';
  return len;
}