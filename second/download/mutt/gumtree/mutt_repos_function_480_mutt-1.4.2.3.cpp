static int link_is_dir (const char *folder, const char *path)
{
  struct stat st;
  char fullpath[_POSIX_PATH_MAX];
  
  snprintf (fullpath, sizeof (fullpath), "%s/%s", folder, path);
  
  if (stat (fullpath, &st) == 0)
    return (S_ISDIR (st.st_mode));
  else
    return 0;
}