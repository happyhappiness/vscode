void recv_exclude_list(int f)
{
  char line[MAXPATHLEN];
  int l;
  while ((l=read_int(f))) {
    read_buf(f,line,l);
    line[l] = 0;
    add_exclude(line);
  }
}