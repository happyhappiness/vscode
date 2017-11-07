static int link_is_dir (const char *folder, const char *path)
{
  struct stat st;
  char fullpath[_POSIX_PATH_MAX];
  
  mutt_concat_path (fullpath, folder, path, sizeof (fullpath));
  
  if (stat (fullpath, &st) == 0)
    return (S_ISDIR (st.st_mode));
  else
    return 0;
}