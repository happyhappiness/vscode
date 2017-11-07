char *mutt_make_date (char *s, size_t len)
{
  time_t t = time (NULL);
  struct tm *l = localtime (&t);
  time_t tz = mutt_local_tz (t);

  tz /= 60;

  snprintf (s, len,  "Date: %s, %d %s %d %02d:%02d:%02d %+03d%02d\n",
	    Weekdays[l->tm_wday], l->tm_mday, Months[l->tm_mon],
	    l->tm_year + 1900, l->tm_hour, l->tm_min, l->tm_sec,
	    (int) tz / 60, (int) abs ((int) tz) % 60);
  return (s);
}