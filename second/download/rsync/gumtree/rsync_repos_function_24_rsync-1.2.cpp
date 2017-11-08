static int writefd(int fd,char *buf,int len)
{
  int total = 0;
  fd_set fds;

  if (buffer_f_in == -1) 
    return write(fd,buf,len);

  while (total < len) {
    int ret = write(fd,buf+total,len-total);

    if (ret == 0) return total;

    if (ret == -1 && errno != EWOULDBLOCK) 
      return total?total:-1;

    if (ret == -1) {
      read_check(buffer_f_in);

      FD_ZERO(&fds);
      FD_SET(fd,&fds);
      select(16,NULL,&fds,NULL,NULL);
    } else {
      total += ret;
    }
  }

  return total;
}