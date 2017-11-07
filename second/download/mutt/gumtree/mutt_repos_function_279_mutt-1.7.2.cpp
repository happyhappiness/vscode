void mutt_folder_hook (char *path)
{
  HOOK *tmp = Hooks;
  BUFFER err, token;

  current_hook_type = MUTT_FOLDERHOOK;

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  mutt_buffer_init (&token);
  for (; tmp; tmp = tmp->next)
  {
    if(!tmp->command)
      continue;

    if (tmp->type & MUTT_FOLDERHOOK)
    {
      if ((regexec (tmp->rx.rx, path, 0, NULL, 0) == 0) ^ tmp->rx.not)
      {
	if (mutt_parse_rc_line (tmp->command, &token, &err) == -1)
	{
	  mutt_error ("%s", err.data);
	  FREE (&token.data);
	  mutt_sleep (1);	/* pause a moment to let the user see the error */
	  current_hook_type = 0;
	  FREE (&err.data);

	  return;
	}
      }
    }
  }
  FREE (&token.data);
  FREE (&err.data);
  
  current_hook_type = 0;
}