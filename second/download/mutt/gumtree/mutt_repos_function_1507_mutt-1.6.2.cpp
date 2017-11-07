int mx_is_mh (const char *path)
{
  char tmp[_POSIX_PATH_MAX];

  snprintf (tmp, sizeof (tmp), "%s/.mh_sequences", path);
  if (access (tmp, F_OK) == 0)
    return 1;

  snprintf (tmp, sizeof (tmp), "%s/.xmhcache", path);
  if (access (tmp, F_OK) == 0)
    return 1;

  snprintf (tmp, sizeof (tmp), "%s/.mew_cache", path);
  if (access (tmp, F_OK) == 0)
    return 1;

  snprintf (tmp, sizeof (tmp), "%s/.mew-cache", path);
  if (access (tmp, F_OK) == 0)
    return 1;

  snprintf (tmp, sizeof (tmp), "%s/.sylpheed_cache", path);
  if (access (tmp, F_OK) == 0)
    return 1;

  /*
   * ok, this isn't an mh folder, but mh mode can be used to read
   * Usenet news from the spool. ;-)
   */

  snprintf (tmp, sizeof (tmp), "%s/.overview", path);
  if (access (tmp, F_OK) == 0)
    return 1;

  return 0;
}