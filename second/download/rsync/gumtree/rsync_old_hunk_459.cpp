  int len=0;
  ioctl(fd,FIONREAD,&len);
  return(len);
}


struct map_struct *map_file(int fd,off_t len)
{
  struct map_struct *ret;
  ret = (struct map_struct *)malloc(sizeof(*ret));
  if (!ret) out_of_memory("map_file");

  ret->map = NULL;
