static int
hcache_open_qdbm (struct header_cache* h, const char* path)
{
  int    flags = VL_OWRITER | VL_OCREAT;

  if (option(OPTHCACHECOMPRESS))
    flags |= VL_OZCOMP;

  h->db = vlopen (path, flags, VL_CMPLEX);
  if (h->db)
    return 0;
  else
    return -1;
}