void crypt_current_time(STATE *s, char *app_name)
{
  time_t t;
  char p[STRING], tmp[STRING];

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
}