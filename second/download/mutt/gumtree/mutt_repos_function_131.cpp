static const char *get_offset (struct tm *tm, const char *s, int sign)
{
  char *ps;
  int offset = strtol (s, &ps, 0);
  if ((sign < 0 && offset > 0) || (sign > 0 && offset < 0))
    offset = -offset;

  switch (*ps)
  {
    case 'y':
      tm->tm_year += offset;
      break;
    case 'm':
      tm->tm_mon += offset;
      break;
    case 'w':
      tm->tm_mday += 7 * offset;
      break;
    case 'd':
      tm->tm_mday += offset;
      break;
    default:
      return s;
  }
  mutt_normalize_time (tm);
  return (ps + 1);
}