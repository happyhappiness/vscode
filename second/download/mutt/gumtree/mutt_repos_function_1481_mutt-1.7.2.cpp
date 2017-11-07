static int mh_already_notified(BUFFY *b, int msgno)
{
  char path[_POSIX_PATH_MAX];
  struct stat sb;

  if ((snprintf(path, sizeof(path), "%s/%d", b->path, msgno) < sizeof(path)) &&
      (stat(path, &sb) == 0))
    return (sb.st_mtime <= b->last_visited);
  return -1;
}