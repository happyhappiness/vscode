void
mutt_hcache_close(header_cache_t *h)
{
  if (!h)
    return;

  gdbm_close(h->db);
  FREE(&h->folder);
  FREE(&h);
}