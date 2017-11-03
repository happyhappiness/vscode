int num_waiting(int fd)
{
  int len=0;
  ioctl(fd,FIONREAD,&len);
  return(len);
}