int
mutt_hcache_store(header_cache_t *h, const char *filename, HEADER * header,
		  unsigned int uidvalidity,
		  size_t(*keylen) (const char *fn),
		  mutt_hcache_store_flags_t flags)
{
  char* data;
  int dlen;
  int ret;
  
  if (!h)
    return -1;
  
  data = mutt_hcache_dump(h, header, &dlen, uidvalidity, flags);
  ret = mutt_hcache_store_raw (h, filename, data, dlen, keylen);
  
  FREE(&data);
  
  return ret;
}