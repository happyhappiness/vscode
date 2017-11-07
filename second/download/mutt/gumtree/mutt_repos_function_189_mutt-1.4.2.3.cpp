void mutt_message_hook (CONTEXT *ctx, HEADER *hdr, int type)
{
  BUFFER err, token;
  HOOK *hook;
  char buf[STRING];

  current_hook_type = type;
  
  err.data = buf;
  err.dsize = sizeof (buf);
  memset (&token, 0, sizeof (token));
  for (hook = Hooks; hook; hook = hook->next)
  {
    if(!hook->command)
      continue;

    if (hook->type & type)
      if ((mutt_pattern_exec (hook->pattern, 0, ctx, hdr) > 0) ^ hook->rx.not)
	if (mutt_parse_rc_line (hook->command, &token, &err) != 0)
	{
	  FREE (&token.data);
	  mutt_error ("%s", err.data);
	  mutt_sleep (1);
	  current_hook_type = 0;
	  return;
	}
  }
  FREE (&token.data);
  current_hook_type = 0;
}