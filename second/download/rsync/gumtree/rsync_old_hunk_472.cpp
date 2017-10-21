  return(len);
}


struct map_struct *map_file(int fd,OFF_T len)
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
  if (len < MAX_MAP_SIZE) {
	  ret->map = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
	  if (ret->map == (char *)-1) {
		  ret->map = NULL;
	  }
  }
#endif
  return ret;
}


char *map_ptr(struct map_struct *map,OFF_T offset,int len)
{
	int nread;

	if (map->map)
		return map->map+offset;

	if (len == 0) 
		return NULL;

	if (len > (map->size-offset))
		len = map->size-offset;

	if (offset >= map->p_offset && 
	    offset+len <= map->p_offset+map->p_len) {
		return (map->p + (offset - map->p_offset));
	}

	len = MAX(len,CHUNK_SIZE);
