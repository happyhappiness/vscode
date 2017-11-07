static int
mutt_addr_hook (char *path, size_t pathlen, int type, CONTEXT *ctx, HEADER *hdr)
{
  HOOK *hook;

  /* determine if a matching hook exists */
  for (hook = Hooks; hook; hook = hook->next)
  {
    if(!hook->command)
      continue;

    if (hook->type & type)
      if ((mutt_pattern_exec (hook->pattern, 0, ctx, hdr) > 0) ^ hook->rx.not)
      {
	mutt_make_string (path, pathlen, hook->command, ctx, hdr);
	return 0;
      }
  }

  return -1;
}