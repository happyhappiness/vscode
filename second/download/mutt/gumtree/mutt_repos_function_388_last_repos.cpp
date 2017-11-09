FILE* mutt_bcache_get(body_cache_t *bcache, const char *id)
{
  char path[_POSIX_PATH_MAX];
  FILE* fp = NULL;

  if (!id || !*id || !bcache)
    return NULL;

  path[0] = '\0';
  safe_strncat (path, sizeof (path), bcache->path, bcache->pathlen);
  safe_strncat (path, sizeof (path), id, mutt_strlen (id));

  fp = safe_fopen (path, "r");

  dprint (3, (debugfile, "bcache: get: '%s': %s\n", path, fp == NULL ? "no" : "yes"));

  return fp;
}