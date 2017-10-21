{
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
  ret->fd = fd;
  ret->size = len;
  ret->p = NULL;
  ret->p_size = 0;
  ret->p_offset = 0;
  ret->p_len = 0;

#ifdef HAVE_MMAP
  if (len < MAX_MAP_SIZE)
    ret->map = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
#endif
  return ret;
}

char *map_ptr(struct map_struct *map,off_t offset,int len)
{
  if (map->map)
    return map->map+offset;

  if (len == 0) 
    return NULL;

  len = MIN(len,map->size-offset);

  if (offset >= map->p_offset && 
      offset+len <= map->p_offset+map->p_len) {
    return (map->p + (offset - map->p_offset));
  }

  len = MAX(len,CHUNK_SIZE);
  len = MIN(len,map->size - offset);  

  if (len > map->p_size) {
    if (map->p) free(map->p);
    map->p = (char *)malloc(len);
    if (!map->p) out_of_memory("map_ptr");
    map->p_size = len;
  }

  if (lseek(map->fd,offset,SEEK_SET) != offset ||
      read(map->fd,map->p,len) != len) {
    fprintf(FERROR,"EOF in map_ptr!\n");
    exit_cleanup(1);
  }

  map->p_offset = offset;
  map->p_len = len;

  return map->p; 
}


void unmap_file(struct map_struct *map)
{
#ifdef HAVE_MMAP
  if (map->map)
    munmap(map->map,map->size);
#endif
  if (map->p) free(map->p);
  free(map);
}


/* this is taken from CVS */
int piped_child(char **command,int *f_in,int *f_out)
{
