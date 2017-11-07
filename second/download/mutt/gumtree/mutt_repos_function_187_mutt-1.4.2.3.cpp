void mutt_folder_hook (char *path)
{
  HOOK *tmp = Hooks;
  BUFFER err, token;
  char buf[STRING];

  current_hook_type = M_FOLDERHOOK;
  
  err.data = buf;
  err.dsize = sizeof (buf);
  memset (&token, 0, sizeof (token));
  for (; tmp; tmp = tmp->next)
  {
    if(!tmp->command)
      continue;

    if (tmp->type & M_FOLDERHOOK)
    {
      if ((regexec (tmp->rx.rx, path, 0, NULL, 0) == 0) ^ tmp->rx.not)
      {
	if (mutt_parse_rc_line (tmp->command, &token, &err) == -1)
	{
	  mutt_error ("%s", err.data);
	  FREE (&token.data);
	  mutt_sleep (1);	/* pause a moment to let the user see the error */
	  current_hook_type = 0;
	  return;
	}
      }
    }
  }
  FREE (&token.data);
  
  current_hook_type = 0;
}