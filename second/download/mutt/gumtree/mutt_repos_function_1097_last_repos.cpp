int
mutt_hcache_delete(header_cache_t *h, const char *filename,
		   size_t(*keylen) (const char *fn))
{
  DBT key;

  if (!h)
    return -1;

  if (filename[0] == '/')
    filename++;

  mutt_hcache_dbt_init(&key, (void *) filename, keylen(filename));
  return h->db->del(h->db, NULL, &key, 0);
}