  if (!WithCrypto)
    return;

  if (option (OPTCRYPTTIMESTAMP))
  {
    t = time(NULL);
    setlocale (LC_TIME, "");
    strftime (p, sizeof (p), _(" (current time: %c)"), localtime (&t));
    setlocale (LC_TIME, "C");
  }
  else
    *p = '\0';

  snprintf (tmp, sizeof (tmp), _("[-- %s output follows%s --]\n"), NONULL(app_name), p);
  state_attach_puts (tmp, s);
