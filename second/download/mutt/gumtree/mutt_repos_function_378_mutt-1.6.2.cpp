FILE* mutt_bcache_put(body_cache_t *bcache, const char *id, int tmp)
{
  char path[_POSIX_PATH_MAX];
  FILE* fp;
  char* s;
  struct stat sb;

  if (!id || !*id || !bcache)
    return NULL;

  snprintf (path, sizeof (path), "%s%s%s", bcache->path, id,
            tmp ? ".tmp" : "");

  if ((fp = safe_fopen (path, "w+")))
    goto out;

  if (errno == EEXIST)
    /* clean up leftover tmp file */
    mutt_unlink (path);

  s = strchr (path + 1, '/');
  while (!(fp = safe_fopen (path, "w+")) && errno == ENOENT && s)
  {
    /* create missing path components */
    *s = '\0';
    if (stat (path, &sb) < 0 && (errno != ENOENT || mkdir (path, 0777) < 0))
      return NULL;
    *s = '/';
    s = strchr (s + 1, '/');
  }

  out:
  dprint (3, (debugfile, "bcache: put: '%s'\n", path));

  return fp;
}