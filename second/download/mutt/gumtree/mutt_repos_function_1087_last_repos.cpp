static int
hcache_open_kc (struct header_cache* h, const char* path)
{
  char fullpath[_POSIX_PATH_MAX];

  /* Kyoto cabinet options are discussed at
   * http://fallabs.com/kyotocabinet/spex.html
   * - rcomp is by default lex, so there is no need to specify it.
   * - opts=l enables linear collision chaining as opposed to using a binary tree.
   *   this isn't suggested unless you are tuning the number of buckets.
   * - opts=c enables compression
   */
  snprintf (fullpath, sizeof(fullpath), "%s#type=kct%s", path,
            option(OPTHCACHECOMPRESS) ? "#opts=c" : "");
  h->db = kcdbnew();
  if (!h->db)
      return -1;
  if (kcdbopen(h->db, fullpath, KCOWRITER | KCOCREATE))
    return 0;
  else
  {
    dprint (2, (debugfile, "kcdbopen failed for %s: %s (ecode %d)\n", fullpath,
                kcdbemsg (h->db), kcdbecode (h->db)));
    kcdbdel(h->db);
    return -1;
  }
}