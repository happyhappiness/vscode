int mutt_bcache_list(body_cache_t *bcache,
		     int (*want_id)(const char *id, body_cache_t *bcache,
				    void *data), void *data)
{
  DIR *d = NULL;
  struct dirent *de;
  int rc = -1;

  if (!bcache || !(d = opendir (bcache->path)))
    goto out;

  rc = 0;

  dprint (3, (debugfile, "bcache: list: dir: '%s'\n", bcache->path));

  while ((de = readdir (d)))
  {
    if (mutt_strncmp (de->d_name, ".", 1) == 0 ||
	mutt_strncmp (de->d_name, "..", 2) == 0)
      continue;

    dprint (3, (debugfile, "bcache: list: dir: '%s', id :'%s'\n", bcache->path, de->d_name));

    if (want_id && want_id (de->d_name, bcache, data) != 0)
      goto out;

    rc++;
  }

out:
  if (d)
  {
    if (closedir (d) < 0)
      rc = -1;
  }
  dprint (3, (debugfile, "bcache: list: did %d entries\n", rc));
  return rc;
}