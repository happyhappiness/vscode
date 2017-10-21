 
 
 void get_checksum2(char *buf,int len,char *sum)
 {
   int i;
   MDstruct MD;
+  static char *buf1 = NULL;
+  static int len1 = 0;
+
+  if (len > len1) {
+    if (buf1) free(buf1);
+    buf1 = (char *)malloc(len+4);
+    len1 = len;
+    if (!buf1) out_of_memory("get_checksum2");
+  }
 
   MDbegin(&MD);
 
-  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
-    bcopy(buf+i,tmpchunk,CSUM_CHUNK);
-    MDupdate(&MD, tmpchunk, CSUM_CHUNK*8);
+  bcopy(buf,buf1,len);
+  if (checksum_seed) {
+    SIVAL(buf1,len,checksum_seed);
+    len += 4;
   }
 
-  bcopy(buf+i,tmpchunk,len-i);
-  MDupdate(&MD, tmpchunk, (len-i)*8);
+  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
+    MDupdate(&MD, buf1+i, CSUM_CHUNK*8);
+  }
+  MDupdate(&MD, buf1+i, (len-i)*8);
 
   sum_put(&MD,sum);
 }
 
 
 void file_checksum(char *fname,char *sum,off_t size)
 {
   int i;
   MDstruct MD;
   char *buf;
   int fd;
   int len = size;
+  char tmpchunk[CSUM_CHUNK];
 
   bzero(sum,csum_length);
 
   fd = open(fname,O_RDONLY);
   if (fd == -1) return;
 
