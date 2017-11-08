static void set_filesystem(char *fname)
{
  struct stat st;
  if (link_stat(fname,&st) != 0) return;
  filesystem_dev = st.st_dev;
}