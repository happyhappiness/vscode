void
mutt_hcache_close(header_cache_t *h)
{
  if (!h)
    return;

  if (!kcdbclose(h->db))
    dprint (2, (debugfile, "kcdbclose failed for %s: %s (ecode %d)\n", h->folder,
                kcdbemsg (h->db), kcdbecode (h->db)));
  kcdbdel(h->db);
  FREE(&h->folder);
  FREE(&h);
}