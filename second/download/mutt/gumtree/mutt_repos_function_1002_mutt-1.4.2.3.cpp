int mutt_check_month (const char *s)
{
  int i;

  for (i = 0; i < 12; i++)
    if (mutt_strncasecmp (s, Months[i], 3) == 0)
      return (i);
  return (-1); /* error */
}