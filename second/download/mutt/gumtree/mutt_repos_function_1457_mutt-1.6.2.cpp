static int mh_sequences_changed(BUFFY *b)
{
  char path[_POSIX_PATH_MAX];
  struct stat sb;

  if ((snprintf(path, sizeof(path), "%s/.mh_sequences", b->path) < sizeof(path)) &&
      (stat(path, &sb) == 0))
    return (sb.st_mtime > b->last_visited);
  return -1;
}