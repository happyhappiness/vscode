void
mutt_hcache_close(header_cache_t *h)
{
  if (!h)
    return;

  vlclose(h->db);
  FREE(&h->folder);
  FREE(&h);
}