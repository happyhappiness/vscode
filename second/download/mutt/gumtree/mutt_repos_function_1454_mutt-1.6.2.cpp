static int mh_read_token (char *t, int *first, int *last)
{
  char *p;
  if ((p = strchr (t, '-')))
  {
    *p++ = '\0';
    if (mutt_atoi (t, first) < 0 || mutt_atoi (p, last) < 0)
      return -1;
  }
  else
  {
    if (mutt_atoi (t, first) < 0)
      return -1;
    *last = *first;
  }
  return 0;
}