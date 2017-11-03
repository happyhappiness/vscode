time_t mutt_decrease_mtime (const char *f, struct stat *st)
{
  struct utimbuf utim;
  struct stat _st;
  time_t mtime;
  
  if (!st)
  {
    if (stat (f, &_st) == -1)
      return -1;
    st = &_st;
  }

  if ((mtime = st->st_mtime) == time (NULL))
  {
    mtime -= 1;
    utim.actime = mtime;
    utim.modtime = mtime;
    utime (f, &utim);
  }
  
  return mtime;
}