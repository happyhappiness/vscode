static char* get_foldername(const char *folder)
{
  char *p = NULL;
  char path[_POSIX_PATH_MAX];
  struct stat st;

  mutt_encode_path (path, sizeof (path), folder);

  /* if the folder is local, canonify the path to avoid
   * to ensure equivalent paths share the hcache */
  if (stat (path, &st) == 0)
  {
    p = safe_malloc (PATH_MAX+1);
    if (!realpath (path, p))
      mutt_str_replace (&p, path);
  } else
    p = safe_strdup (path);

  return p;
}