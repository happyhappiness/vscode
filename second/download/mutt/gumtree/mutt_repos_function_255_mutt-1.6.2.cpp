int mbox_check_empty (const char *path)
{
  struct stat st;

  if (stat (path, &st) == -1)
    return -1;

  return ((st.st_size == 0));
}