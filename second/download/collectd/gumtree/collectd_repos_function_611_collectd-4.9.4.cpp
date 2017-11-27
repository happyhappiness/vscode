static int fc_read_dir_callback (const char *dirname, const char *filename,
    void *user_data)
{
  fc_directory_conf_t *dir = user_data;
  char abs_path[PATH_MAX];
  struct stat statbuf;
  int status;

  if (dir == NULL)
    return (-1);

  ssnprintf (abs_path, sizeof (abs_path), "%s/%s", dirname, filename);

  status = lstat (abs_path, &statbuf);
  if (status != 0)
  {
    ERROR ("filecount plugin: stat (%s) failed.", abs_path);
    return (-1);
  }

  if (S_ISDIR (statbuf.st_mode) && (dir->options & FC_RECURSIVE))
  {
    status = walk_directory (abs_path, fc_read_dir_callback, dir);
    return (status);
  }
  else if (!S_ISREG (statbuf.st_mode))
  {
    return (0);
  }

  if (dir->name != NULL)
  {
    status = fnmatch (dir->name, filename, /* flags = */ 0);
    if (status != 0)
      return (0);
  }

  if (dir->mtime != 0)
  {
    time_t mtime = dir->now;

    if (dir->mtime < 0)
      mtime += dir->mtime;
    else
      mtime -= dir->mtime;

    DEBUG ("filecount plugin: Only collecting files that were touched %s %u.",
        (dir->mtime < 0) ? "after" : "before",
        (unsigned int) mtime);

    if (((dir->mtime < 0) && (statbuf.st_mtime < mtime))
        || ((dir->mtime > 0) && (statbuf.st_mtime > mtime)))
      return (0);
  }

  if (dir->size != 0)
  {
    off_t size;

    if (dir->size < 0)
      size = (off_t) ((-1) * dir->size);
    else
      size = (off_t) dir->size;

    if (((dir->size < 0) && (statbuf.st_size > size))
        || ((dir->size > 0) && (statbuf.st_size < size)))
      return (0);
  }

  dir->files_num++;
  dir->files_size += (uint64_t) statbuf.st_size;

  return (0);
}