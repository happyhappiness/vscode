void mutt_account_hook (const char* url)
{
  /* parsing commands with URLs in an account hook can cause a recursive
   * call. We just skip processing if this occurs. Typically such commands
   * belong in a folder-hook -- perhaps we should warn the user. */
  static int inhook = 0;

  HOOK* hook;
  BUFFER token;
  BUFFER err;

  if (inhook)
    return;

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  mutt_buffer_init (&token);

  for (hook = Hooks; hook; hook = hook->next)
  {
    if (! (hook->command && (hook->type & MUTT_ACCOUNTHOOK)))
      continue;

    if ((regexec (hook->rx.rx, url, 0, NULL, 0) == 0) ^ hook->rx.not)
    {
      inhook = 1;

      if (mutt_parse_rc_line (hook->command, &token, &err) == -1)
      {
	FREE (&token.data);
	mutt_error ("%s", err.data);
	FREE (&err.data);
	mutt_sleep (1);

        inhook = 0;
	return;
      }

      inhook = 0;
    }
  }

  FREE (&token.data);
  FREE (&err.data);
}