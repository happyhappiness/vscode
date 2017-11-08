static void set_filesystem(char *fname)
{
  struct stat st;
  if (lstat(fname,&st) != 0) return;
  filesystem_dev = st.st_dev;
}