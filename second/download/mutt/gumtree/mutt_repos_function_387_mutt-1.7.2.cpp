int mutt_bcache_del(body_cache_t *bcache, const char *id)
{
  char path[_POSIX_PATH_MAX];

  if (!id || !*id || !bcache)
    return -1;

  path[0] = '\0';
  safe_strncat (path, sizeof (path), bcache->path, bcache->pathlen);
  safe_strncat (path, sizeof (path), id, mutt_strlen (id));

  dprint (3, (debugfile, "bcache: del: '%s'\n", path));

  return unlink (path);
}