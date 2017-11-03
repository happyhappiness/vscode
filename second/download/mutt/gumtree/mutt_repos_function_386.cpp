int mutt_bcache_move(body_cache_t* bcache, const char* id, const char* newid)
{
  char path[_POSIX_PATH_MAX];
  char newpath[_POSIX_PATH_MAX];

  if (!bcache || !id || !*id || !newid || !*newid)
    return -1;

  snprintf (path, sizeof (path), "%s%s", bcache->path, id);
  snprintf (newpath, sizeof (newpath), "%s%s", bcache->path, newid);

  dprint (3, (debugfile, "bcache: mv: '%s' '%s'\n", path, newpath));

  return rename (path, newpath);
}