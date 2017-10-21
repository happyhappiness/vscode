 
 
 
 static off_t last_match;
 
 
-static void matched(int f,struct sum_struct *s,char *buf,off_t len,int offset,int i)
+static void matched(int f,struct sum_struct *s,char *buf,off_t len,
+		    int offset,int i)
 {
   int n = offset - last_match;
   
   if (verbose > 2)
     if (i != -1)
       fprintf(stderr,"match at %d last_match=%d j=%d len=%d n=%d\n",
 	      (int)offset,(int)last_match,i,(int)s->sums[i].len,n);
 
   if (n > 0) {
+    int l = 0;
     write_int(f,n);
-    write_buf(f,buf+last_match,n);
+    while (l < n) {
+      int n1 = MIN(WRITE_BLOCK_SIZE,n-l);
+      write_buf(f,map_ptr(buf,last_match+l,n1),n1);
+      l += n1;
+    }
     data_transfer += n;
   }
   write_int(f,-(i+1));
   if (i != -1)
     last_match = offset + s->sums[i].len;
   if (n > 0)
