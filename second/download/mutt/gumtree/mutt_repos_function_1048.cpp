int
mutt_hcache_delete(header_cache_t *h, const char *filename,
		   size_t(*keylen) (const char *fn))
{
  char path[_POSIX_PATH_MAX];
  int ksize;

  if (!h)
    return -1;

  strncpy(path, h->folder, sizeof (path));
  safe_strcat(path, sizeof (path), filename);

  ksize = strlen(h->folder) + keylen(path + strlen(h->folder));

  return tcbdbout(h->db, path, ksize);
}