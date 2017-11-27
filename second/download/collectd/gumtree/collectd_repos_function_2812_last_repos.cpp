int format_rfc3339(char *buffer, size_t buffer_size, struct tm const *t_tm,
                   long nsec, _Bool print_nano, char const *zone) /* {{{ */
{
  int len;
  char *pos = buffer;
  size_t size_left = buffer_size;

  if ((len = strftime(pos, size_left, "%Y-%m-%dT%H:%M:%S", t_tm)) == 0)
    return ENOMEM;
  pos += len;
  size_left -= len;

  if (print_nano) {
    if ((len = snprintf(pos, size_left, ".%09ld", nsec)) == 0)
      return ENOMEM;
    pos += len;
    size_left -= len;
  }

  sstrncpy(pos, zone, size_left);
  return 0;
}