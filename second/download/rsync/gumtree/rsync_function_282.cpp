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