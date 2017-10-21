  Utilities used in rsync 

  tridge, June 1996
  */
#include "rsync.h"

int num_waiting(int fd)
{
  int len=0;
  ioctl(fd,FIONREAD,&len);
  return(len);
}

char *map_file(int fd,off_t len)
{
  char *ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
  return ret;
}

