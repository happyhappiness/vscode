time_t mutt_parse_date (const char *s, HEADER *h)
{
  int count = 0;
  char *t;
  int hour, min, sec;
  struct tm tm;
  int i;
  int tz_offset = 0;
  int zhours = 0;
  int zminutes = 0;
  int zoccident = 0;
  const char *ptz;
  char tzstr[SHORT_STRING];
  char scratch[SHORT_STRING];

  /* Don't modify our argument. Fixed-size buffer is ok here since
   * the date format imposes a natural limit. 
   */

  strfcpy (scratch, s, sizeof (scratch));
  
  /* kill the day of the week, if it exists. */
  if ((t = strchr (scratch, ',')))
    t++;
  else
    t = scratch;
  t = skip_email_wsp(t);

  memset (&tm, 0, sizeof (tm));

  while ((t = strtok (t, " \t")) != NULL)
  {
    switch (count)
    {
      case 0: /* day of the month */
	if (mutt_atoi (t, &tm.tm_mday) < 0 || tm.tm_mday < 0)
	  return (-1);
	if (tm.tm_mday > 31)
	  return (-1);
	break;

      case 1: /* month of the year */
	if ((i = mutt_check_month (t)) < 0)
	  return (-1);
	tm.tm_mon = i;
	break;

      case 2: /* year */
	if (mutt_atoi (t, &tm.tm_year) < 0 || tm.tm_year < 0)
	  return (-1);
        if (tm.tm_year < 50)
	  tm.tm_year += 100;
        else if (tm.tm_year >= 1900)
	  tm.tm_year -= 1900;
	break;

      case 3: /* time of day */
	if (sscanf (t, "%d:%d:%d", &hour, &min, &sec) == 3)
	  ;
	else if (sscanf (t, "%d:%d", &hour, &min) == 2)
	  sec = 0;
	else
	{
	  dprint(1, (debugfile, "parse_date: could not process time format: %s\n", t));
	  return(-1);
	}
	tm.tm_hour = hour;
	tm.tm_min = min;
	tm.tm_sec = sec;
	break;

      case 4: /* timezone */
	/* sometimes we see things like (MST) or (-0700) so attempt to
	 * compensate by uncommenting the string if non-RFC822 compliant
	 */
	ptz = uncomment_timezone (tzstr, sizeof (tzstr), t);

	if (*ptz == '+' || *ptz == '-')
	{
	  if (ptz[1] && ptz[2] && ptz[3] && ptz[4]
	      && isdigit ((unsigned char) ptz[1]) && isdigit ((unsigned char) ptz[2])
	      && isdigit ((unsigned char) ptz[3]) && isdigit ((unsigned char) ptz[4]))
	  {
	    zhours = (ptz[1] - '0') * 10 + (ptz[2] - '0');
	    zminutes = (ptz[3] - '0') * 10 + (ptz[4] - '0');

	    if (ptz[0] == '-')
	      zoccident = 1;
	  }
	}
	else
	{
	  struct tz_t *tz;

	  tz = bsearch (ptz, TimeZones, sizeof TimeZones/sizeof (struct tz_t),
			sizeof (struct tz_t),
			(int (*)(const void *, const void *)) ascii_strcasecmp
			/* This is safe to do: A pointer to a struct equals
			 * a pointer to its first element*/);

	  if (tz)
	  {
	    zhours = tz->zhours;
	    zminutes = tz->zminutes;
	    zoccident = tz->zoccident;
	  }

	  /* ad hoc support for the European MET (now officially CET) TZ */
	  if (ascii_strcasecmp (t, "MET") == 0)
	  {
	    if ((t = strtok (NULL, " \t")) != NULL)
	    {
	      if (!ascii_strcasecmp (t, "DST"))
		zhours++;
	    }
	  }
	}
	tz_offset = zhours * 3600 + zminutes * 60;
	if (!zoccident)
	  tz_offset = -tz_offset;
	break;
    }
    count++;
    t = 0;
  }

  if (count < 4) /* don't check for missing timezone */
  {
    dprint(1,(debugfile, "parse_date(): error parsing date format, using received time\n"));
    return (-1);
  }

  if (h)
  {
    h->zhours = zhours;
    h->zminutes = zminutes;
    h->zoccident = zoccident;
  }

  return (mutt_mktime (&tm, 0) + tz_offset);
}