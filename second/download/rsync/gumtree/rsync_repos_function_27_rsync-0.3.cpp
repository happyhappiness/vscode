char *map_file(int fd,off_t len)
{
  char *ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
  return ret;
}