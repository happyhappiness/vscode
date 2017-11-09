static int
hcache_open_tc (struct header_cache* h, const char* path)
{
  h->db = tcbdbnew();
  if (!h->db)
      return -1;
  if (option(OPTHCACHECOMPRESS))
    tcbdbtune(h->db, 0, 0, 0, -1, -1, BDBTDEFLATE);
  if (tcbdbopen(h->db, path, BDBOWRITER | BDBOCREAT))
    return 0;
  else
  {
#ifdef DEBUG
    int ecode = tcbdbecode (h->db);
    dprint (2, (debugfile, "tcbdbopen failed for %s: %s (ecode %d)\n", path, tcbdberrmsg (ecode), ecode));
#endif
    tcbdbdel(h->db);
    return -1;
  }
}