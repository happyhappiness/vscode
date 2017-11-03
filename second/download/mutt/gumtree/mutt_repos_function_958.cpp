static char *tls_make_date (time_t t, char *s, size_t len)
{
  struct tm *l = gmtime (&t);

  if (l)
    snprintf (s, len,  "%s, %d %s %d %02d:%02d:%02d UTC",
	      Weekdays[l->tm_wday], l->tm_mday, Months[l->tm_mon],
	      l->tm_year + 1900, l->tm_hour, l->tm_min, l->tm_sec);
  else
    strfcpy (s, _("[invalid date]"), len);

  return (s);
}