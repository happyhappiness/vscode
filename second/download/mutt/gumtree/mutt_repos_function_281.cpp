void mutt_message_hook (CONTEXT *ctx, HEADER *hdr, int type)
{
  BUFFER err, token;
  HOOK *hook;

  current_hook_type = type;

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  mutt_buffer_init (&token);
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
	  FREE (&err.data);

	  return;
	}
  }
  FREE (&token.data);
  FREE (&err.data);

  current_hook_type = 0;
}