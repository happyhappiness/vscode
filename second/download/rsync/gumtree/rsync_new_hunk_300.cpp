  if (l2 > 0)
    lseek(f,l2,SEEK_CUR);

  return len;
}


static int writefd(int fd,char *buf,int len)
{
  int total = 0;
  fd_set w_fds, r_fds;
  int fd_count, count, got_select=0;
