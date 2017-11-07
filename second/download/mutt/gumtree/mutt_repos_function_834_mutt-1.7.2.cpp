time_t mutt_local_tz (time_t t)
{
  struct tm *ptm;
  struct tm utc;

  if (!t)
    t = time (NULL);
  ptm = gmtime (&t);
  /* need to make a copy because gmtime/localtime return a pointer to
     static memory (grr!) */
  memcpy (&utc, ptm, sizeof (utc));
  return (compute_tz (t, &utc));
}