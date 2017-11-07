int mx_is_maildir (const char *path)
{
  char tmp[_POSIX_PATH_MAX];
  struct stat st;

  snprintf (tmp, sizeof (tmp), "%s/cur", path);
  if (stat (tmp, &st) == 0 && S_ISDIR (st.st_mode))
    return 1;
  return 0;
}