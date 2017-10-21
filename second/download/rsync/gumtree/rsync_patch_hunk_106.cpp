 {
   int len=0;
   ioctl(fd,FIONREAD,&len);
   return(len);
 }
 
+static int map_fd = -1;
+static off_t map_size = 0;
+static char *p = NULL;
+static int p_size = 0;
+static int p_offset = 0;
+static int p_len = 0;
+
+
 char *map_file(int fd,off_t len)
 {
-  char *ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
+  char *ret = NULL;
+#ifdef HAVE_MMAP
+  if (len < MAX_MAP_SIZE)
+    ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
+#endif
+  map_fd = fd;
+  map_size = len; 
   return ret;
 }
 
+char *map_ptr(char *buf,off_t offset,int len)
+{
+  if (buf)
+    return buf+offset;
+
+  if (len == 0) 
+    return NULL;
+
+  len = MIN(len,map_size-offset);
+
+  if (offset >= p_offset && 
+      offset+len <= p_offset+p_len) {
+    return (p + (offset - p_offset));
+  }
+
+  len = MAX(len,WRITE_BLOCK_SIZE);
+  len = MIN(len,map_size - offset);  
+
+  if (len > p_size) {
+    if (p) free(p);
+    p = (char *)malloc(len);
+    if (!p) out_of_memory("map_ptr");
+    p_size = len;
+  }
+
+  if (lseek(map_fd,offset,SEEK_SET) != offset ||
+      read(map_fd,p,len) != len) {
+    fprintf(stderr,"EOF in map_ptr!\n");
+    exit(1);
+  }
+
+  p_offset = offset;
+  p_len = len;
+
+  return p; 
+}
+
+
 void unmap_file(char *buf,off_t len)
 {
   if (len > 0 && buf)
     munmap(buf,len);
+  map_fd = -1;
+  map_size = 0;
+  p_len = 0;
 }
 
 
 /* this is taken from CVS */
 int piped_child(char **command,int *f_in,int *f_out)
 {
