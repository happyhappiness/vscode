static void pgp_current_time (STATE *s)
{
  time_t t;
  char p[STRING];

  t = time (NULL);
  setlocale (LC_TIME, "");
  strftime (p, sizeof (p),
	    _("[-- PGP output follows (current time: %c) --]\n"),
	    localtime (&t));
  setlocale (LC_TIME, "C");
  state_attach_puts (p, s);
}