static int
mutt_addr_hook (char *path, size_t pathlen, int type, CONTEXT *ctx, HEADER *hdr)
{
  HOOK *hook;
  pattern_cache_t cache;

  memset (&cache, 0, sizeof (cache));
  /* determine if a matching hook exists */
  for (hook = Hooks; hook; hook = hook->next)
  {
    if(!hook->command)
      continue;

    if (hook->type & type)
      if ((mutt_pattern_exec (hook->pattern, 0, ctx, hdr, &cache) > 0) ^ hook->rx.not)
      {
	mutt_make_string (path, pathlen, hook->command, ctx, hdr);
	return 0;
      }
  }

  return -1;
}