static int bcache_path(ACCOUNT *account, const char *mailbox,
		       char *dst, size_t dstlen)
{
  char host[STRING];
  char path[_POSIX_PATH_MAX];
  ciss_url_t url;
  int len;

  if (!account || !MessageCachedir || !*MessageCachedir || !dst || !dstlen)
    return -1;

  /* make up a ciss_url_t we can turn into a string */
  memset (&url, 0, sizeof (ciss_url_t));
  mutt_account_tourl (account, &url);
  /*
   * mutt_account_tourl() just sets up some pointers;
   * if this ever changes, we have a memleak here
   */
  url.path = NULL;
  if (url_ciss_tostring (&url, host, sizeof (host), U_PATH) < 0)
  {
    dprint (1, (debugfile, "bcache_path: URL to string failed\n"));
    return -1;
  }

  mutt_encode_path (path, sizeof (path), NONULL (mailbox));

  len = snprintf (dst, dstlen-1, "%s/%s%s%s", MessageCachedir,
		  host, path,
		  (*path && path[mutt_strlen (path) - 1] == '/') ? "" : "/");

  dprint (3, (debugfile, "bcache_path: rc: %d, path: '%s'\n", len, dst));

  if (len < 0 || (size_t)len >= dstlen-1)
    return -1;

  dprint (3, (debugfile, "bcache_path: directory: '%s'\n", dst));

  return 0;
}