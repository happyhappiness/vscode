void *
mutt_hcache_fetch(header_cache_t *h, const char *filename,
		  size_t(*keylen) (const char *fn))
{
  void* data;

  data = mutt_hcache_fetch_raw (h, filename, keylen);

  if (!data || !crc_matches(data, h->crc))
  {
    mutt_hcache_free (&data);
    return NULL;
  }
  
  return data;
}