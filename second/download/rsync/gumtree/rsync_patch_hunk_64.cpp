 {
   if (len > 0)
     munmap(buf,len);
 }
 
 
+int read_write(int fd_in,int fd_out,int size)
+{
+  static char *buf=NULL;
+  static int bufsize = WRITE_BLOCK_SIZE;
+  int total=0;
+  
+  if (!buf) {
+    buf = (char *)malloc(bufsize);
+    if (!buf) out_of_memory("read_write");
+  }
+
+  while (total < size) {
+    int n = MIN(size-total,bufsize);
+    read_buf(fd_in,buf,n);
+    if (write(fd_out,buf,n) != n)
+      return total;
+    total += n;
+  }
+  return total;
+}
+
+
 /* this is taken from CVS */
 int piped_child(char **command,int *f_in,int *f_out)
 {
   int pid;
   int to_child_pipe[2];
   int from_child_pipe[2];
