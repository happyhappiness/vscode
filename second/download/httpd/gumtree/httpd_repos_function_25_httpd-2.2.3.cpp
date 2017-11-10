void nonblock(int fd)
{
  int i=1;
  ioctl(fd, FIONBIO, &i);
}