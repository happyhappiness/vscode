static int
hcache_open_gdbm (struct header_cache* h, const char* path)
{
  int pagesize;

  if (mutt_atoi (HeaderCachePageSize, &pagesize) < 0 || pagesize <= 0)
    pagesize = 16384;

  h->db = gdbm_open((char *) path, pagesize, GDBM_WRCREAT, 00600, NULL);
  if (h->db)
    return 0;

  /* if rw failed try ro */
  h->db = gdbm_open((char *) path, pagesize, GDBM_READER, 00600, NULL);
  if (h->db)
    return 0;

  return -1;
}