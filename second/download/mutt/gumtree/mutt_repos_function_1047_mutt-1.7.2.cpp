void
mutt_hcache_close(header_cache_t *h)
{
  if (!h)
    return;

  if (!tcbdbclose(h->db))
  {
#ifdef DEBUG
    int ecode = tcbdbecode (h->db);
    dprint (2, (debugfile, "tcbdbclose failed for %s: %s (ecode %d)\n", h->folder, tcbdberrmsg (ecode), ecode));
#endif
  }
  tcbdbdel(h->db);
  FREE(&h->folder);
  FREE(&h);
}