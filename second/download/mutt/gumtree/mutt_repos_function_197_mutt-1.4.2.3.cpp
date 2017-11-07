void mutt_account_hook (const char* url)
{
  HOOK* hook;
  BUFFER token;
  BUFFER err;
  char buf[STRING];

  err.data = buf;
  err.dsize = sizeof (buf);
  memset (&token, 0, sizeof (token));

  for (hook = Hooks; hook; hook = hook->next)
  {
    if (! (hook->command && (hook->type & M_ACCOUNTHOOK)))
      continue;

    if ((regexec (hook->rx.rx, url, 0, NULL, 0) == 0) ^ hook->rx.not)
    {
      if (mutt_parse_rc_line (hook->command, &token, &err) == -1)
      {
	FREE (&token.data);
	mutt_error ("%s", err.data);
	mutt_sleep (1);

	return;
      }
    }
  }

  FREE (&token.data);
}