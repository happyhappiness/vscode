char *map_file(int fd,off_t len)
{
  char *ret = NULL;
#ifdef HAVE_MMAP
  if (len < MAX_MAP_SIZE)
    ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
#endif
  map_fd = fd;
  map_size = len; 
  return ret;
}