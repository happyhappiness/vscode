static void mh_read_token (char *t, int *first, int *last)
{
  char *p;
  if ((p = strchr (t, '-')))
  {
    *p++ = '\0';
    *first = atoi (t);
    *last  = atoi (p);
  }
  else
    *first = *last = atoi (t);
}