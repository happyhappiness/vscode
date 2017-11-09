int
mutt_hcache_delete(header_cache_t *h, const char *filename,
		   size_t(*keylen) (const char *fn))
{
  datum key;
  char path[_POSIX_PATH_MAX];

  if (!h)
    return -1;

  strncpy(path, h->folder, sizeof (path));
  safe_strcat(path, sizeof (path), filename);

  key.dptr = path;
  key.dsize = strlen(h->folder) + keylen(path + strlen(h->folder));

  return gdbm_delete(h->db, key);
}