    if (map->p) free(map->p);
    map->p = (char *)malloc(len);
    if (!map->p) out_of_memory("map_ptr");
    map->p_size = len;
  }

  if (lseek(map->fd,offset,SEEK_SET) != offset ||
      (nread=read(map->fd,map->p,len)) != len) {
	  fprintf(FERROR,"EOF in map_ptr! (offset=%d len=%d nread=%d errno=%d)\n",
		  (int)offset, len, nread, errno);
	  exit_cleanup(1);
  }

  map->p_offset = offset;
  map->p_len = len;
