time_t
curl_getdate (const char *p, const time_t *now)
{
  struct tm tm, tm0, *tmp;
  time_t Start;
  CURL_CONTEXT cookie;
#ifdef HAVE_LOCALTIME_R
  struct tm keeptime;
#endif
  cookie.yyInput = p;
  Start = now ? *now : time ((time_t *) NULL);
#ifdef HAVE_LOCALTIME_R
  tmp = (struct tm *)localtime_r(&Start, &keeptime);
#else
  tmp = localtime (&Start);
#endif
  if (!tmp)
    return -1;
  cookie.yyYear = tmp->tm_year + TM_YEAR_ORIGIN;
  cookie.yyMonth = tmp->tm_mon + 1;
  cookie.yyDay = tmp->tm_mday;
  cookie.yyHour = tmp->tm_hour;
  cookie.yyMinutes = tmp->tm_min;
  cookie.yySeconds = tmp->tm_sec;
  tm.tm_isdst = tmp->tm_isdst;
  cookie.yyMeridian = MER24;
  cookie.yyRelSeconds = 0;
  cookie.yyRelMinutes = 0;
  cookie.yyRelHour = 0;
  cookie.yyRelDay = 0;
  cookie.yyRelMonth = 0;
  cookie.yyRelYear = 0;
  cookie.yyHaveDate = 0;
  cookie.yyHaveDay = 0;
  cookie.yyHaveRel = 0;
  cookie.yyHaveTime = 0;
  cookie.yyHaveZone = 0;

  if (yyparse (&cookie)
      || cookie.yyHaveTime > 1 || cookie.yyHaveZone > 1 ||
      cookie.yyHaveDate > 1 || cookie.yyHaveDay > 1)
    return -1;

  tm.tm_year = ToYear (cookie.yyYear) - TM_YEAR_ORIGIN + cookie.yyRelYear;
  tm.tm_mon = cookie.yyMonth - 1 + cookie.yyRelMonth;
  tm.tm_mday = cookie.yyDay + cookie.yyRelDay;
  if (cookie.yyHaveTime ||
      (cookie.yyHaveRel && !cookie.yyHaveDate && !cookie.yyHaveDay))
    {
      tm.tm_hour = ToHour (cookie.yyHour, cookie.yyMeridian);
      if (tm.tm_hour < 0)
	return -1;
      tm.tm_min = cookie.yyMinutes;
      tm.tm_sec = cookie.yySeconds;
    }
  else
    {
      tm.tm_hour = tm.tm_min = tm.tm_sec = 0;
    }
  tm.tm_hour += cookie.yyRelHour;
  tm.tm_min += cookie.yyRelMinutes;
  tm.tm_sec += cookie.yyRelSeconds;

  /* Let mktime deduce tm_isdst if we have an absolute timestamp,
     or if the relative timestamp mentions days, months, or years.  */
  if (cookie.yyHaveDate | cookie.yyHaveDay | cookie.yyHaveTime |
      cookie.yyRelDay | cookie.yyRelMonth | cookie.yyRelYear)
    tm.tm_isdst = -1;

  tm0 = tm;

  Start = mktime (&tm);

  if (Start == (time_t) -1)
    {

      /* Guard against falsely reporting errors near the time_t boundaries
         when parsing times in other time zones.  For example, if the min
         time_t value is 1970-01-01 00:00:00 UTC and we are 8 hours ahead
         of UTC, then the min localtime value is 1970-01-01 08:00:00; if
         we apply mktime to 1970-01-01 00:00:00 we will get an error, so
         we apply mktime to 1970-01-02 08:00:00 instead and adjust the time
         zone by 24 hours to compensate.  This algorithm assumes that
         there is no DST transition within a day of the time_t boundaries.  */
      if (cookie.yyHaveZone)
	{
	  tm = tm0;
	  if (tm.tm_year <= EPOCH - TM_YEAR_ORIGIN)
	    {
	      tm.tm_mday++;
	      cookie.yyTimezone -= 24 * 60;
	    }
	  else
	    {
	      tm.tm_mday--;
	      cookie.yyTimezone += 24 * 60;
	    }
	  Start = mktime (&tm);
	}

      if (Start == (time_t) -1)
	return Start;
    }

  if (cookie.yyHaveDay && !cookie.yyHaveDate)
    {
      tm.tm_mday += ((cookie.yyDayNumber - tm.tm_wday + 7) % 7
		     + 7 * (cookie.yyDayOrdinal - (0 < cookie.yyDayOrdinal)));
      Start = mktime (&tm);
      if (Start == (time_t) -1)
	return Start;
    }

  if (cookie.yyHaveZone)
    {
      long delta;
      struct tm *gmt;
#ifdef HAVE_GMTIME_R
      /* thread-safe version */
      struct tm keeptime;
      gmt = (struct tm *)gmtime_r(&Start, &keeptime);
#else
      gmt = gmtime(&Start);
#endif
      if (!gmt)
	return -1;
      delta = cookie.yyTimezone * 60L + difftm (&tm, gmt);
      if ((Start + delta < Start) != (delta < 0))
	return -1;		/* time_t overflow */
      Start += delta;
    }

  return Start;
}