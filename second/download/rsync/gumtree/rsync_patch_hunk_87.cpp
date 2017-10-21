   Utilities used in rsync 
 
   tridge, June 1996
   */
 #include "rsync.h"
 
-static int total_written = 0;
-static int total_read = 0;
-
-extern int verbose;
-
-int write_total(void)
-{
-  return total_written;
-}
-
-int read_total(void)
-{
-  return total_read;
-}
-
-void write_int(int f,int x)
-{
-  char b[4];
-  SIVAL(b,0,x);
-  if (write(f,b,4) != 4) {
-    fprintf(stderr,"write_int failed : %s\n",strerror(errno));
-    exit(1);
-  }
-  total_written += 4;
-}
-
-void write_buf(int f,char *buf,int len)
-{
-  if (write(f,buf,len) != len) {
-    fprintf(stderr,"write_buf failed : %s\n",strerror(errno));
-    exit(1);
-  }
-  total_written += len;
-}
-
-static int num_waiting(int fd)
+int num_waiting(int fd)
 {
   int len=0;
-#ifdef FIONREAD
   ioctl(fd,FIONREAD,&len);
-#endif
   return(len);
 }
 
-static char *read_buffer = NULL;
-static char *read_buffer_p = NULL;
-static int read_buffer_len = 0;
-static int read_buffer_size = 0;
-
-
-void write_flush(int f)
-{
-}
-
-
-/* This function was added to overcome a deadlock problem when using
- * ssh.  It looks like we can't allow our receive queue to get full or
- * ssh will clag up. Uggh.  */
-void read_check(int f)
-{
-  int n;
-
-  if (read_buffer_len == 0) {
-    read_buffer_p = read_buffer;
-  }
-
-  if ((n=num_waiting(f)) <= 0)
-    return;
-
-  if (read_buffer_p != read_buffer) {
-    memmove(read_buffer,read_buffer_p,read_buffer_len);
-    read_buffer_p = read_buffer;
-  }
-
-  if (n > (read_buffer_size - read_buffer_len)) {
-    read_buffer_size += n;
-    if (!read_buffer)
-      read_buffer = (char *)malloc(read_buffer_size);
-    else
-      read_buffer = (char *)realloc(read_buffer,read_buffer_size);
-    if (!read_buffer) out_of_memory("read check");      
-    read_buffer_p = read_buffer;      
-  }
-
-  n = read(f,read_buffer+read_buffer_len,n);
-  if (n > 0) {
-    read_buffer_len += n;
-  }
-}
-
-
-static int readfd(int fd,char *buffer,int N)
-{
-  int  ret;
-  int total=0;  
- 
-  while (total < N)
-    {
-      if (read_buffer_len > 0) {
-	ret = MIN(read_buffer_len,N-total);
-	memcpy(buffer+total,read_buffer_p,ret);
-	read_buffer_p += ret;
-	read_buffer_len -= ret;
-      } else {
-	ret = read(fd,buffer + total,N - total);
-      }
-
-      if (ret <= 0)
-	return total;
-      total += ret;
-    }
-  return total;
-}
-
-
-int read_int(int f)
-{
-  char b[4];
-  if (readfd(f,b,4) != 4) {
-    if (verbose > 1) 
-      fprintf(stderr,"Error reading %d bytes : %s\n",4,strerror(errno));
-    exit(1);
-  }
-  total_read += 4;
-  return IVAL(b,0);
-}
-
-void read_buf(int f,char *buf,int len)
-{
-  if (readfd(f,buf,len) != len) {
-    if (verbose > 1) 
-      fprintf(stderr,"Error reading %d bytes : %s\n",len,strerror(errno));
-    exit(1);
-  }
-  total_read += len;
-}
-
-
 char *map_file(int fd,off_t len)
 {
   char *ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
   return ret;
 }
 
