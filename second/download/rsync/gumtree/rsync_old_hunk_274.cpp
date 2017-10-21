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

