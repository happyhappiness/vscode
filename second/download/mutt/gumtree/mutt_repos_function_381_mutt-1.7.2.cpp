body_cache_t *mutt_bcache_open (ACCOUNT *account, const char *mailbox)
{
  struct body_cache *bcache = NULL;

  if (!account)
    goto bail;

  bcache = safe_calloc (1, sizeof (struct body_cache));
  if (bcache_path (account, mailbox, bcache->path,
		   sizeof (bcache->path)) < 0)
    goto bail;
  bcache->pathlen = mutt_strlen (bcache->path);

  return bcache;

bail:
  if (bcache)
    FREE(&bcache);
  return NULL;
}