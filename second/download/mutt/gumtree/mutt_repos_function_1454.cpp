static int is_day_name (const char *s)
{
  int i;

  if ((strlen (s) < 3) || !*(s + 3) || !ISSPACE (*(s+3)))
    return 0;
  for (i=0; i<7; i++)
    if (mutt_strncasecmp (s, Weekdays[i], 3) == 0)
      return 1;
  return 0;
}