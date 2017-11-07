static const char *
mutt_hcache_per_folder(const char *path, const char *folder,
                       hcache_namer_t namer)
{
  static char hcpath[_POSIX_PATH_MAX];
  struct stat sb;
  unsigned char md5sum[16];
  char* s;
  int ret, plen;
#ifndef HAVE_ICONV
  const char *chs = Charset && *Charset ? Charset : 
		    mutt_get_default_charset ();
#endif

  plen = mutt_strlen (path);

  ret = stat(path, &sb);
  if (ret < 0 && path[plen-1] != '/')
  {
#ifdef HAVE_ICONV
    return path;
#else
    snprintf (hcpath, _POSIX_PATH_MAX, "%s-%s", path, chs);
    return hcpath;
#endif
  }

  if (ret >= 0 && !S_ISDIR(sb.st_mode))
  {
#ifdef HAVE_ICONV
    return path;
#else
    snprintf (hcpath, _POSIX_PATH_MAX, "%s-%s", path, chs);
    return hcpath;
#endif
  }

  if (namer)
  {
    snprintf (hcpath, sizeof (hcpath), "%s%s", path,
              path[plen-1] == '/' ? "" : "/");
    if (path[plen-1] != '/')
      plen++;

    ret = namer (folder, hcpath + plen, sizeof (hcpath) - plen);
  }
  else
  {
    md5_buffer (folder, strlen (folder), &md5sum);

    /* On some systems (e.g. OS X), snprintf is defined as a macro.
     * Embedding directives inside macros is undefined, so we have to duplicate
     * the whole call:
     */
#ifndef HAVE_ICONV
    ret = snprintf(hcpath, _POSIX_PATH_MAX,
                   "%s/%02x%02x%02x%02x%02x%02x%02x%02x"
                   "%02x%02x%02x%02x%02x%02x%02x%02x"
		   "-%s"
		   ,
		   path, md5sum[0], md5sum[1], md5sum[2], md5sum[3],
                   md5sum[4], md5sum[5], md5sum[6], md5sum[7], md5sum[8],
                   md5sum[9], md5sum[10], md5sum[11], md5sum[12],
                   md5sum[13], md5sum[14], md5sum[15]
		   ,chs
		   );
#else
    ret = snprintf(hcpath, _POSIX_PATH_MAX,
                   "%s/%02x%02x%02x%02x%02x%02x%02x%02x"
                   "%02x%02x%02x%02x%02x%02x%02x%02x"
		   ,
		   path, md5sum[0], md5sum[1], md5sum[2], md5sum[3],
                   md5sum[4], md5sum[5], md5sum[6], md5sum[7], md5sum[8],
                   md5sum[9], md5sum[10], md5sum[11], md5sum[12],
                   md5sum[13], md5sum[14], md5sum[15]
		   );
#endif
  }
  
  if (ret <= 0)
    return path;

  if (stat (hcpath, &sb) >= 0)
    return hcpath;

  s = strchr (hcpath + 1, '/');
  while (s)
  {
    /* create missing path components */
    *s = '\0';
    if (stat (hcpath, &sb) < 0 && (errno != ENOENT || mkdir (hcpath, 0777) < 0))
      return path;
    *s = '/';
    s = strchr (s + 1, '/');
  }

  return hcpath;
}