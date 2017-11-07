time_t mutt_mktime (struct tm *t, int local)
{
  time_t g;

  static int AccumDaysPerMonth[12] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
  };

  /* Compute the number of days since January 1 in the same year */
  g = AccumDaysPerMonth [t->tm_mon % 12];

  /* The leap years are 1972 and every 4. year until 2096,
   * but this algoritm will fail after year 2099 */
  g += t->tm_mday;
  if ((t->tm_year % 4) || t->tm_mon < 2)
    g--;
  t->tm_yday = g;

  /* Compute the number of days since January 1, 1970 */
  g += (t->tm_year - 70) * 365;
  g += (t->tm_year - 69) / 4;

  /* Compute the number of hours */
  g *= 24;
  g += t->tm_hour;

  /* Compute the number of minutes */
  g *= 60;
  g += t->tm_min;

  /* Compute the number of seconds */
  g *= 60;
  g += t->tm_sec;

  if (local)
    g -= compute_tz (g, t);

  return (g);
}