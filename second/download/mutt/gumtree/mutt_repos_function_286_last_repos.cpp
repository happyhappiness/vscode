void mutt_message_hook (CONTEXT *ctx, HEADER *hdr, int type)
{
  BUFFER err, token;
  HOOK *hook;
  pattern_cache_t cache;

  current_hook_type = type;

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  mutt_buffer_init (&token);
  memset (&cache, 0, sizeof (cache));
  for (hook = Hooks; hook; hook = hook->next)
  {
    if(!hook->command)
      continue;

    if (hook->type & type)
      if ((mutt_pattern_exec (hook->pattern, 0, ctx, hdr, &cache) > 0) ^ hook->rx.not)
      {
	if (mutt_parse_rc_line (hook->command, &token, &err) != 0)
	{
	  FREE (&token.data);
	  mutt_error ("%s", err.data);
	  mutt_sleep (1);
	  current_hook_type = 0;
	  FREE (&err.data);

	  return;
	}
        /* Executing arbitrary commands could affect the pattern results,
         * so the cache has to be wiped */
        memset (&cache, 0, sizeof (cache));
      }
  }
  FREE (&token.data);
  FREE (&err.data);

  current_hook_type = 0;
}