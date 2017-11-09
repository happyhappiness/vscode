static time_t compute_tz (time_t g, struct tm *utc)
{
  struct tm *lt = localtime (&g);
  time_t t;
  int yday;

  t = (((lt->tm_hour - utc->tm_hour) * 60) + (lt->tm_min - utc->tm_min)) * 60;

  if ((yday = (lt->tm_yday - utc->tm_yday)))
  {
    /* This code is optimized to negative timezones (West of Greenwich) */
    if (yday == -1 ||	/* UTC passed midnight before localtime */
	yday > 1)	/* UTC passed new year before localtime */
      t -= 24 * 60 * 60;
    else
      t += 24 * 60 * 60;
  }

  return t;
}