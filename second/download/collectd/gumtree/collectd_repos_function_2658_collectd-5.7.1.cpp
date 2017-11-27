int format_rfc3339_local(char *buffer, size_t buffer_size, cdtime_t t,
                         _Bool print_nano) /* {{{ */
{
  struct tm t_tm;
  long nsec = 0;
  int status;
  char zone[7]; /* +00:00 */

  if ((status = get_local_time(t, &t_tm, &nsec)) != 0)
    return status; /* The error should have already be reported. */

  if ((status = format_zone(zone, sizeof(zone), &t_tm)) != 0)
    return status;

  return format_rfc3339(buffer, buffer_size, &t_tm, nsec, print_nano, zone);
}