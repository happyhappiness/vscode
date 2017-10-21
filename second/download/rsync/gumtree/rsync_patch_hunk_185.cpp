 }
 
 
 static off_t last_match;
 
 
-static void matched(int f,struct sum_struct *s,char *buf,off_t len,
+static void matched(int f,struct sum_struct *s,struct map_struct *buf,
+		    off_t len,
 		    int offset,int i)
 {
   int n = offset - last_match;
-  
+  int j;
+
   if (verbose > 2)
     if (i != -1)
       fprintf(FERROR,"match at %d last_match=%d j=%d len=%d n=%d\n",
 	      (int)offset,(int)last_match,i,(int)s->sums[i].len,n);
 
-  if (n > 0) {
-    int l = 0;
-    write_int(f,n);
-    while (l < n) {
-      int n1 = MIN(CHUNK_SIZE,n-l);
-      write_buf(f,map_ptr(buf,last_match+l,n1),n1);
-      l += n1;
-    }
-    data_transfer += n;
+  send_token(f,i,buf,last_match,n,i==-1?0:s->sums[i].len);
+  data_transfer += n;
+
+  if (n > 0)
+    write_flush(f);
+
+  if (i != -1)
+    n += s->sums[i].len;
+  
+  for (j=0;j<n;j+=CHUNK_SIZE) {
+    int n1 = MIN(CHUNK_SIZE,n-j);
+    sum_update(map_ptr(buf,last_match+j,n1),n1);
   }
-  write_int(f,-(i+1));
+
+
   if (i != -1)
     last_match = offset + s->sums[i].len;
-  if (n > 0)
-    write_flush(f);
+
+}
+
+
+static inline char *window_ptr(struct map_struct *buf,int off,int len)
+{
+  static char *p=NULL;
+  static int p_len = 0;
+  static int p_off = 0;  
+
+  if (off == 0) {
+    p_off = 0;
+    p_len = CHUNK_SIZE;
+    p = map_ptr(buf,p_off,p_len);    
+  }
+
+  while (off+len > p_off+p_len) {
+    p_off += CHUNK_SIZE;
+    p_len = CHUNK_SIZE;
+    p = map_ptr(buf,p_off,p_len);  
+  }
+
+  return(p + (off-p_off));
 }
 
 
-static void hash_search(int f,struct sum_struct *s,char *buf,off_t len)
+static void hash_search(int f,struct sum_struct *s,
+			struct map_struct *buf,off_t len)
 {
   int offset,j,k;
   int end;
   char sum2[SUM_LENGTH];
   uint32 s1, s2, sum; 
   char *map;
 
   if (verbose > 2)
     fprintf(FERROR,"hash search b=%d len=%d\n",s->n,(int)len);
 
   k = MIN(len, s->n);
 
-  map = map_ptr(buf,0,k);
+  map = window_ptr(buf,0,k);
 
   sum = get_checksum1(map, k);
   s1 = sum & 0xFFFF;
   s2 = sum >> 16;
   if (verbose > 3)
     fprintf(FERROR, "sum=%.8x k=%d\n", sum, k);
