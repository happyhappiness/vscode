static int fbh_check_file (fbhash_t *h) /* {{{ */
{
  struct stat statbuf = { 0 };
  int status;

  status = stat (h->filename, &statbuf);
  if (status != 0)
    return (-1);

  if (h->mtime >= statbuf.st_mtime)
    return (0);

  status = fbh_read_file (h);
  if (status == 0)
    h->mtime = statbuf.st_mtime;

  return (status);
}