
  if (offset >= p_offset && 
      offset+len <= p_offset+p_len) {
    return (p + (offset - p_offset));
  }

  len = MAX(len,WRITE_BLOCK_SIZE);
  len = MIN(len,map_size - offset);  

  if (len > p_size) {
    if (p) free(p);
    p = (char *)malloc(len);
    if (!p) out_of_memory("map_ptr");
    p_size = len;
  }

  if (lseek(map_fd,offset,SEEK_SET) != offset ||
      read(map_fd,p,len) != len) {
    fprintf(stderr,"EOF in map_ptr!\n");
    exit(1);
  }

  p_offset = offset;
  p_len = len;

  return p; 
