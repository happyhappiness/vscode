 	}
 	return ret;
 }
 
 
 
+/* this provides functionality somewhat similar to mmap() but using
+   read(). It gives sliding window access to a file. mmap() is not
+   used because of the possibility of another program (such as a
+   mailer) truncating the file thus giving us a SIGBUS */
 struct map_struct *map_file(int fd,OFF_T len)
 {
-	struct map_struct *ret;
-	ret = (struct map_struct *)malloc(sizeof(*ret));
-	if (!ret) out_of_memory("map_file");
-
-	ret->map = NULL;
-	ret->fd = fd;
-	ret->size = len;
-	ret->p = NULL;
-	ret->p_size = 0;
-	ret->p_offset = 0;
-	ret->p_len = 0;
-
-#ifdef USE_MMAP
-	len = MIN(len, MAX_MAP_SIZE);
-	ret->map = (char *)do_mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
-	if (ret->map == (char *)-1) {
-		ret->map = NULL;
-	} else {
-		ret->p_len = len;
-	}
-#endif
-	return ret;
-}
+	struct map_struct *map;
+	map = (struct map_struct *)malloc(sizeof(*map));
+	if (!map) out_of_memory("map_file");
+
+	map->fd = fd;
+	map->file_size = len;
+	map->p = NULL;
+	map->p_size = 0;
+	map->p_offset = 0;
+	map->p_fd_offset = 0;
+	map->p_len = 0;
 
+	return map;
+}
 
+/* slide the read window in the file */
 char *map_ptr(struct map_struct *map,OFF_T offset,int len)
 {
 	int nread;
+	OFF_T window_start, read_start;
+	int window_size, read_size, read_offset;
 
-	if (len == 0) 
+	if (len == 0) {
 		return NULL;
+	}
 
-	if (len > (map->size-offset))
-		len = map->size-offset;
-
-#ifdef USE_MMAP
-	if (map->map) {
-		if (offset >= map->p_offset && 
-		    offset+len <= map->p_offset+map->p_len) {
-			return (map->map + (offset - map->p_offset));
-		}
-		if (munmap(map->map, map->p_len) != 0) {
-			rprintf(FERROR,"munmap failed : %s\n", strerror(errno));
-			exit_cleanup(RERR_MALLOC);
-		}
-
-		/* align the mmap region on a nice boundary back a bit from
-		   where it is asked for to allow for some seeking */
-		if (offset > 2*CHUNK_SIZE) {
-			map->p_offset = offset - 2*CHUNK_SIZE;
-			map->p_offset &= ~((OFF_T)(CHUNK_SIZE-1));
-		} else {
-			map->p_offset = 0;
-		}
-		
-		/* map up to MAX_MAP_SIZE */
-		map->p_len = MAX(len, MAX_MAP_SIZE);
-		map->p_len = MIN(map->p_len, map->size - map->p_offset);
-
-		map->map = (char *)do_mmap(NULL,map->p_len,PROT_READ,
-					   MAP_SHARED,map->fd,map->p_offset);
-
-		if (map->map == (char *)-1) {
-			map->map = NULL;
-			map->p_len = 0;
-			map->p_offset = 0;
-		} else {
-			return (map->map + (offset - map->p_offset));
-		}
+	/* can't go beyond the end of file */
+	if (len > (map->file_size - offset)) {
+		len = map->file_size - offset;
 	}
-#endif
 
+	/* in most cases the region will already be available */
 	if (offset >= map->p_offset && 
 	    offset+len <= map->p_offset+map->p_len) {
 		return (map->p + (offset - map->p_offset));
 	}
 
-	len = MAX(len,CHUNK_SIZE);
-	if (len > (map->size-offset))
-		len = map->size-offset;
-
-	if (len > map->p_size) {
-		if (map->p) free(map->p);
-		map->p = (char *)malloc(len);
-		if (!map->p) out_of_memory("map_ptr");
-		map->p_size = len;
+
+	/* nope, we are going to have to do a read. Work out our desired window */
+	if (offset > 2*CHUNK_SIZE) {
+		window_start = offset - 2*CHUNK_SIZE;
+		window_start &= ~((OFF_T)(CHUNK_SIZE-1)); /* assumes power of 2 */
+	} else {
+		window_start = 0;
+	}
+	window_size = MAX_MAP_SIZE;
+	if (window_start + window_size > map->file_size) {
+		window_size = map->file_size - window_start;
+	}
+	if (offset + len > window_start + window_size) {
+		window_size = (offset+len) - window_start;
 	}
 
-	map->p_offset = offset;
-	map->p_len = len;
+	/* make sure we have allocated enough memory for the window */
+	if (window_size > map->p_size) {
+		map->p = (char *)Realloc(map->p, window_size);
+		if (!map->p) out_of_memory("map_ptr");
+		map->p_size = window_size;
+	}
 
-	if (do_lseek(map->fd,offset,SEEK_SET) != offset) {
-		rprintf(FERROR,"lseek failed in map_ptr\n");
-		exit_cleanup(RERR_FILEIO);
+	/* now try to avoid re-reading any bytes by reusing any bytes from the previous
+	   buffer. */
+	if (window_start >= map->p_offset &&
+	    window_start < map->p_offset + map->p_len &&
+	    window_start + window_size >= map->p_offset + map->p_len) {
+		read_start = map->p_offset + map->p_len;
+		read_offset = read_start - window_start;
+		read_size = window_size - read_offset;
+		memmove(map->p, map->p + (map->p_len - read_offset), read_offset);
+	} else {
+		read_start = window_start;
+		read_size = window_size;
+		read_offset = 0;
 	}
 
-	if ((nread=read(map->fd,map->p,len)) != len) {		
-		if (nread < 0) nread = 0;
-		/* the best we can do is zero the buffer - the file
-                   has changed mid transfer! */
-		memset(map->p+nread, 0, len - nread);
+	if (read_size <= 0) {
+		rprintf(FINFO,"Warning: unexpected read size of %d in map_ptr\n", read_size);
+	} else {
+		if (map->p_fd_offset != read_start) {
+			if (do_lseek(map->fd,read_start,SEEK_SET) != read_start) {
+				rprintf(FERROR,"lseek failed in map_ptr\n");
+				exit_cleanup(RERR_FILEIO);
+			}
+			map->p_fd_offset = read_start;
+		}
+
+		if ((nread=read(map->fd,map->p + read_offset,read_size)) != read_size) {
+			if (nread < 0) nread = 0;
+			/* the best we can do is zero the buffer - the file
+			   has changed mid transfer! */
+			memset(map->p+read_offset+nread, 0, read_size - nread);
+		}
+		map->p_fd_offset += nread;
 	}
+
+	map->p_offset = window_start;
+	map->p_len = window_size;
   
-	return map->p; 
+	return map->p + (offset - map->p_offset); 
 }
 
 
 void unmap_file(struct map_struct *map)
 {
-#ifdef USE_MMAP
-	if (map->map) {
-		munmap(map->map,map->p_len);
-		map->map = NULL;
-	}
-#endif
 	if (map->p) {
 		free(map->p);
 		map->p = NULL;
 	}
 	memset(map, 0, sizeof(*map));
 	free(map);
