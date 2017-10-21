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

void unmap_file(char *buf,off_t len)
{
  if (len > 0 && buf)
    munmap(buf,len);
}


/* this is taken from CVS */
int piped_child(char **command,int *f_in,int *f_out)
{
