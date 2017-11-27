int format_rfc3339_utc(char *buffer, size_t buffer_size, cdtime_t t,
                       _Bool print_nano) /* {{{ */
{
  struct tm t_tm;
  long nsec = 0;
  int status;

  if ((status = get_utc_time(t, &t_tm, &nsec)) != 0)
    return status; /* The error should have already be reported. */

  return format_rfc3339(buffer, buffer_size, &t_tm, nsec, print_nano,
                        zulu_zone);
}