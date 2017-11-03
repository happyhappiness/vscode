static int
dotlock_unlink (const char *realpath)
{
  struct stat lsb;
  int i = -1;

  if (dotlock_lock (realpath) != DL_EX_OK)
    return DL_EX_ERROR;

  if ((i = lstat (realpath, &lsb)) == 0 && lsb.st_size == 0)
    unlink (realpath);

  dotlock_unlock (realpath);

  return (i == 0) ?  DL_EX_OK : DL_EX_ERROR;
}