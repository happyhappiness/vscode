 {
   int len=0;
   ioctl(fd,FIONREAD,&len);
   return(len);
 }
 
-static int map_fd = -1;
-static off_t map_size = 0;
-static char *p = NULL;
-static int p_size = 0;
-static int p_offset = 0;
-static int p_len = 0;
 
-
-char *map_file(int fd,off_t len)
+struct map_struct *map_file(int fd,off_t len)
 {
-  char *ret = NULL;
+  struct map_struct *ret;
+  ret = (struct map_struct *)malloc(sizeof(*ret));
+  if (!ret) out_of_memory("map_file");
+
+  ret->map = NULL;
+  ret->fd = fd;
+  ret->size = len;
+  ret->p = NULL;
+  ret->p_size = 0;
+  ret->p_offset = 0;
+  ret->p_len = 0;
+
 #ifdef HAVE_MMAP
   if (len < MAX_MAP_SIZE)
-    ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
+    ret->map = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
 #endif
-  map_fd = fd;
-  map_size = len; 
   return ret;
 }
 
-char *map_ptr(char *buf,off_t offset,int len)
+char *map_ptr(struct map_struct *map,off_t offset,int len)
 {
-  if (buf)
-    return buf+offset;
+  if (map->map)
+    return map->map+offset;
 
   if (len == 0) 
     return NULL;
 
-  len = MIN(len,map_size-offset);
+  len = MIN(len,map->size-offset);
 
-  if (offset >= p_offset && 
-      offset+len <= p_offset+p_len) {
-    return (p + (offset - p_offset));
+  if (offset >= map->p_offset && 
+      offset+len <= map->p_offset+map->p_len) {
+    return (map->p + (offset - map->p_offset));
   }
 
   len = MAX(len,CHUNK_SIZE);
-  len = MIN(len,map_size - offset);  
+  len = MIN(len,map->size - offset);  
 
-  if (len > p_size) {
-    if (p) free(p);
-    p = (char *)malloc(len);
-    if (!p) out_of_memory("map_ptr");
-    p_size = len;
+  if (len > map->p_size) {
+    if (map->p) free(map->p);
+    map->p = (char *)malloc(len);
+    if (!map->p) out_of_memory("map_ptr");
+    map->p_size = len;
   }
 
-  if (lseek(map_fd,offset,SEEK_SET) != offset ||
-      read(map_fd,p,len) != len) {
+  if (lseek(map->fd,offset,SEEK_SET) != offset ||
+      read(map->fd,map->p,len) != len) {
     fprintf(FERROR,"EOF in map_ptr!\n");
     exit_cleanup(1);
   }
 
-  p_offset = offset;
-  p_len = len;
+  map->p_offset = offset;
+  map->p_len = len;
 
-  return p; 
+  return map->p; 
 }
 
 
-void unmap_file(char *buf,off_t len)
+void unmap_file(struct map_struct *map)
 {
 #ifdef HAVE_MMAP
-  if (len > 0 && buf)
-    munmap(buf,len);
+  if (map->map)
+    munmap(map->map,map->size);
 #endif
-  map_fd = -1;
-  map_size = 0;
-  p_len = 0;
+  if (map->p) free(map->p);
+  free(map);
 }
 
 
 /* this is taken from CVS */
 int piped_child(char **command,int *f_in,int *f_out)
 {
