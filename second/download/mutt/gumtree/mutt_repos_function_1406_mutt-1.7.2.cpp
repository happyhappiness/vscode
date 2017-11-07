void mutt_set_mtime (const char* from, const char* to)
{
  struct utimbuf utim;
  struct stat st;

  if (stat (from, &st) != -1)
  {
    utim.actime = st.st_mtime;
    utim.modtime = st.st_mtime;
    utime (to, &utim);
  }
}