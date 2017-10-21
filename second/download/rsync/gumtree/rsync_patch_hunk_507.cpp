   return ret;
 }
 
 
 char *map_ptr(struct map_struct *map,OFF_T offset,int len)
 {
-  int nread = -2;
+	int nread;
 
-  if (map->map)
-    return map->map+offset;
+	if (map->map)
+		return map->map+offset;
 
-  if (len == 0) 
-    return NULL;
+	if (len == 0) 
+		return NULL;
 
-  if (len > (map->size-offset))
-      len = map->size-offset;
-
-  if (offset >= map->p_offset && 
-      offset+len <= map->p_offset+map->p_len) {
-    return (map->p + (offset - map->p_offset));
-  }
-
-  len = MAX(len,CHUNK_SIZE);
-  if (len > (map->size-offset))
-      len = map->size-offset;
-
-  if (len > map->p_size) {
-    if (map->p) free(map->p);
-    map->p = (char *)malloc(len);
-    if (!map->p) out_of_memory("map_ptr");
-    map->p_size = len;
-  }
-
-  if (do_lseek(map->fd,offset,SEEK_SET) != offset ||
-      (nread=read(map->fd,map->p,len)) != len) {
-	  rprintf(FERROR,"EOF in map_ptr! (offset=%d len=%d nread=%d errno=%d)\n",
-		  (int)offset, len, nread, errno);
-	  exit_cleanup(1);
-  }
-
-  map->p_offset = offset;
-  map->p_len = len;
-
-  return map->p; 
+	if (len > (map->size-offset))
+		len = map->size-offset;
+
+	if (offset >= map->p_offset && 
+	    offset+len <= map->p_offset+map->p_len) {
+		return (map->p + (offset - map->p_offset));
+	}
+
+	len = MAX(len,CHUNK_SIZE);
+	if (len > (map->size-offset))
+		len = map->size-offset;
+
+	if (len > map->p_size) {
+		if (map->p) free(map->p);
+		map->p = (char *)malloc(len);
+		if (!map->p) out_of_memory("map_ptr");
+		map->p_size = len;
+	}
+
+	map->p_offset = offset;
+	map->p_len = len;
+
+	if (do_lseek(map->fd,offset,SEEK_SET) != offset) {
+		rprintf(FERROR,"lseek failed in map_ptr\n");
+		exit_cleanup(1);
+	}
+
+	if ((nread=read(map->fd,map->p,len)) != len) {		
+		if (nread < 0) nread = 0;
+		/* the best we can do is zero the buffer - the file
+                   has changed mid transfer! */
+		memset(map->p+nread, 0, len - nread);
+	}
+  
+	return map->p; 
 }
 
 
 void unmap_file(struct map_struct *map)
 {
 #ifdef HAVE_MMAP
