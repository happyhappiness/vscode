static size_t maildir_hcache_keylen (const char *fn)
{
  const char * p = strrchr (fn, ':');
  return p ? (size_t) (p - fn) : mutt_strlen(fn);
}