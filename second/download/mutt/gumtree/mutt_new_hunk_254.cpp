  if (!WithCrypto)
    return;

  if (option (OPTCRYPTTIMESTAMP))
  {
    t = time(NULL);
    strftime (p, sizeof (p), _(" (current time: %c)"), localtime (&t));
  }
  else
    *p = '\0';

  snprintf (tmp, sizeof (tmp), _("[-- %s output follows%s --]\n"), NONULL(app_name), p);
  state_attach_puts (tmp, s);
