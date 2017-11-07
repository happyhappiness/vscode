void mutt_bcache_close (body_cache_t **bcache)
{
  if (!bcache || !*bcache)
    return;
  FREE(bcache);			/* __FREE_CHECKED__ */
}