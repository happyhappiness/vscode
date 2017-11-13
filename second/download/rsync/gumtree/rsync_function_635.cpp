char *map_ptr(struct map_struct *map,OFF_T offset,int len)
{
	int nread;

	if (len == 0) 
		return NULL;

	if (len > (map->size-offset))
		len = map->size-offset;

#ifdef USE_MMAP
	if (map->map) {
		if (offset >= map->p_offset && 
		    offset+len <= map->p_offset+map->p_len) {
			return (map->map + (offset - map->p_offset));
		}
		if (munmap(map->map, map->p_len) != 0) {
			rprintf(FERROR,"munmap failed : %s\n", strerror(errno));
			exit_cleanup(1);
		}

		/* align the mmap region on a nice boundary back a bit from
		   where it is asked for to allow for some seeking */
		if (offset > 2*CHUNK_SIZE) {
			map->p_offset = offset - 2*CHUNK_SIZE;
			map->p_offset &= ~((OFF_T)(CHUNK_SIZE-1));
		} else {
			map->p_offset = 0;
		}
		
		/* map up to MAX_MAP_SIZE */
		map->p_len = MAX(len, MAX_MAP_SIZE);
		map->p_len = MIN(map->p_len, map->size - map->p_offset);

		map->map = (char *)do_mmap(NULL,map->p_len,PROT_READ,
					   MAP_SHARED,map->fd,map->p_offset);

		if (map->map == (char *)-1) {
			map->map = NULL;
			map->p_len = 0;
			map->p_offset = 0;
		} else {
			return (map->map + (offset - map->p_offset));
		}
	}
#endif

	if (offset >= map->p_offset && 
	    offset+len <= map->p_offset+map->p_len) {
		return (map->p + (offset - map->p_offset));
	}

	len = MAX(len,CHUNK_SIZE);
	if (len > (map->size-offset))
		len = map->size-offset;

	if (len > map->p_size) {
		if (map->p) free(map->p);
		map->p = (char *)malloc(len);
		if (!map->p) out_of_memory("map_ptr");
		map->p_size = len;
	}

	map->p_offset = offset;
	map->p_len = len;

	if (do_lseek(map->fd,offset,SEEK_SET) != offset) {
		rprintf(FERROR,"lseek failed in map_ptr\n");
		exit_cleanup(1);
	}

	if ((nread=read(map->fd,map->p,len)) != len) {		
		if (nread < 0) nread = 0;
		/* the best we can do is zero the buffer - the file
                   has changed mid transfer! */
		memset(map->p+nread, 0, len - nread);
	}
  
	return map->p; 
}