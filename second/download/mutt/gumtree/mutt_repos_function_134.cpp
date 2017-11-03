static int eat_date (pattern_t *pat, BUFFER *s, BUFFER *err)
{
  BUFFER buffer;
  struct tm min, max;
  char *pexpr;

  mutt_buffer_init (&buffer);
  pexpr = s->dptr;
  if (mutt_extract_token (&buffer, s, MUTT_TOKEN_COMMENT | MUTT_TOKEN_PATTERN) != 0
      || !buffer.data)
  {
    snprintf (err->data, err->dsize, _("Error in expression: %s"), pexpr);
    return (-1);
  }
  if (!*buffer.data)
  {
    snprintf (err->data, err->dsize, _("Empty expression"));
    return (-1);
  }

  memset (&min, 0, sizeof (min));
  /* the `0' time is Jan 1, 1970 UTC, so in order to prevent a negative time
     when doing timezone conversion, we use Jan 2, 1970 UTC as the base
     here */
  min.tm_mday = 2;
  min.tm_year = 70;

  memset (&max, 0, sizeof (max));

  /* Arbitrary year in the future.  Don't set this too high
     or mutt_mktime() returns something larger than will
     fit in a time_t on some systems */
  max.tm_year = 130;
  max.tm_mon = 11;
  max.tm_mday = 31;
  max.tm_hour = 23;
  max.tm_min = 59;
  max.tm_sec = 59;

  if (strchr ("<>=", buffer.data[0]))
  {
    /* offset from current time
       <3d	less than three days ago
       >3d	more than three days ago
       =3d	exactly three days ago */
    time_t now = time (NULL);
    struct tm *tm = localtime (&now);
    int exact = 0;

    if (buffer.data[0] == '<')
    {
      memcpy (&min, tm, sizeof (min));
      tm = &min;
    }
    else
    {
      memcpy (&max, tm, sizeof (max));
      tm = &max;

      if (buffer.data[0] == '=')
	exact++;
    }
    tm->tm_hour = 23;
    tm->tm_min = tm->tm_sec = 59;

    /* force negative offset */
    get_offset (tm, buffer.data + 1, -1);

    if (exact)
    {
      /* start at the beginning of the day in question */
      memcpy (&min, &max, sizeof (max));
      min.tm_hour = min.tm_sec = min.tm_min = 0;
    }
  }
  else
  {
    const char *pc = buffer.data;

    int haveMin = FALSE;
    int untilNow = FALSE;
    if (isdigit ((unsigned char)*pc))
    {
      /* minimum date specified */
      if ((pc = getDate (pc, &min, err)) == NULL)
      {
	FREE (&buffer.data);
	return (-1);
      }
      haveMin = TRUE;
      SKIPWS (pc);
      if (*pc == '-')
      {
        const char *pt = pc + 1;
	SKIPWS (pt);
	untilNow = (*pt == '\0');
      }
    }

    if (!untilNow)
    { /* max date or relative range/window */

      struct tm baseMin;

      if (!haveMin)
      { /* save base minimum and set current date, e.g. for "-3d+1d" */
	time_t now = time (NULL);
	struct tm *tm = localtime (&now);
	memcpy (&baseMin, &min, sizeof(baseMin));
	memcpy (&min, tm, sizeof (min));
	min.tm_hour = min.tm_sec = min.tm_min = 0;
      }
      
      /* preset max date for relative offsets,
	 if nothing follows we search for messages on a specific day */
      max.tm_year = min.tm_year;
      max.tm_mon = min.tm_mon;
      max.tm_mday = min.tm_mday;

      if (!parse_date_range (pc, &min, &max, haveMin, &baseMin, err))
      { /* bail out on any parsing error */
	FREE (&buffer.data);
	return (-1);
      }
    }
  }

  /* Since we allow two dates to be specified we'll have to adjust that. */
  adjust_date_range (&min, &max);

  pat->min = mutt_mktime (&min, 1);
  pat->max = mutt_mktime (&max, 1);

  FREE (&buffer.data);

  return 0;
}