    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
 #include "rsync.h"
 
-extern int csum_length;
+int csum_length=SUM_LENGTH;
+
+#define CSUM_CHUNK 64
+
+static char *tmpchunk = NULL;
+
 
 /*
   a simple 32 bit checksum that can be upadted from either end
   (inspired by Mark Adler's Adler-32 checksum)
   */
 uint32 get_checksum1(char *buf,int len)
 {
     int i;
     uint32 s1, s2;
 
     s1 = s2 = 0;
-    for (i = 0; i < len; i++) {
-	s1 += buf[i];
-	s2 += s1;
+    for (i = 0; i < (len-4); i+=4) {
+	s2 += 4*(s1 + buf[i]) + 3*buf[i+1] + 2*buf[i+2] + buf[i+3];
+	s1 += (buf[i+0] + buf[i+1] + buf[i+2] + buf[i+3]); 
+    }
+    for (; i < len; i++) {
+	s1 += buf[i]; s2 += s1;
     }
     return (s1 & 0xffff) + (s2 << 16);
 }
 
 
+static void sum_put(MDstruct *md,char *sum)
+{
+  SIVAL(sum,0,md->buffer[0]);
+  if (csum_length <= 4) return;
+  SIVAL(sum,4,md->buffer[1]);
+  if (csum_length <= 8) return;
+  SIVAL(sum,8,md->buffer[2]);
+  if (csum_length <= 12) return;
+  SIVAL(sum,12,md->buffer[3]);
+}
+
+
 void get_checksum2(char *buf,int len,char *sum)
 {
-  char buf2[64];
   int i;
   MDstruct MD;
 
   MDbegin(&MD);
-  for(i = 0; i + 64 <= len; i += 64) {
-    bcopy(buf+i,buf2,64);
-    MDupdate(&MD, buf2, 512);
+
+  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
+    bcopy(buf+i,tmpchunk,CSUM_CHUNK);
+    MDupdate(&MD, tmpchunk, CSUM_CHUNK*8);
   }
-  bcopy(buf+i,buf2,len-i);
-  MDupdate(&MD, buf2, (len-i)*8);
-  SIVAL(sum,0,MD.buffer[0]);
-  if (csum_length <= 4) return;
-  SIVAL(sum,4,MD.buffer[1]);
-  if (csum_length <= 8) return;
-  SIVAL(sum,8,MD.buffer[2]);
-  if (csum_length <= 12) return;
-  SIVAL(sum,12,MD.buffer[3]);
+
+  bcopy(buf+i,tmpchunk,len-i);
+  MDupdate(&MD, tmpchunk, (len-i)*8);
+
+  sum_put(&MD,sum);
 }
 
+
 void file_checksum(char *fname,char *sum,off_t size)
 {
+  int i;
+  MDstruct MD;
   char *buf;
   int fd;
+  int len = size;
+
   bzero(sum,csum_length);
 
   fd = open(fname,O_RDONLY);
   if (fd == -1) return;
 
   buf = map_file(fd,size);
-  if (!buf) {
-    close(fd);
-    return;
+
+  MDbegin(&MD);
+
+  for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
+    bcopy(map_ptr(buf,i,CSUM_CHUNK),tmpchunk,CSUM_CHUNK);
+    MDupdate(&MD, tmpchunk, CSUM_CHUNK*8);
   }
 
-  get_checksum2(buf,size,sum);
+  bcopy(map_ptr(buf,i,len-i),tmpchunk,len-i);
+  MDupdate(&MD, tmpchunk, (len-i)*8);
+
+  sum_put(&MD,sum);
+
   close(fd);
   unmap_file(buf,size);
 }
+
+
+void checksum_init(void)
+{
+  tmpchunk = (char *)malloc(CSUM_CHUNK);
+  if (!tmpchunk) out_of_memory("checksum_init");
+}
+
+
+#ifdef CHECKSUM_MAIN
+ int main(int argc,char *argv[])
+{
+  char sum[SUM_LENGTH];
+  int i,j;
+
+  checksum_init();
+
+  for (i=1;i<argc;i++) {
+    struct stat st;
+    if (stat(argv[i],&st) == 0) {
+      file_checksum(argv[i],sum,st.st_size);
+      for (j=0;j<SUM_LENGTH;j++)
+	printf("%02X",(unsigned char)sum[j]);
+      printf("  %s\n",argv[i]);
+    }
+  }
+}
+#endif
