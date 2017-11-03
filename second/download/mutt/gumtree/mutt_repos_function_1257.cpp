char *mutt_gen_msgid (void)
{
  char buf[SHORT_STRING];
  time_t now;
  struct tm *tm;
  const char *fqdn;

  now = time (NULL);
  tm = gmtime (&now);
  if(!(fqdn = mutt_fqdn(0)))
    fqdn = NONULL(Hostname);

  snprintf (buf, sizeof (buf), "<%d%02d%02d%02d%02d%02d.G%c%u@%s>",
	    tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour,
	    tm->tm_min, tm->tm_sec, MsgIdPfx, (unsigned int)getpid (), fqdn);
  MsgIdPfx = (MsgIdPfx == 'Z') ? 'A' : MsgIdPfx + 1;
  return (safe_strdup (buf));
}