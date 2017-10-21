 
       map = map_ptr(buf,offset2,len);
 
       see_token(map, len);
       sum_update(map,len);
 
-      if (write_sparse(fd,map,len) != len) {
+      if (fd != -1 && write_sparse(fd,map,len) != len) {
 	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += len;
     }
   }
 
-  if (offset > 0 && sparse_end(fd) != 0) {
+  if (fd != -1 && offset > 0 && sparse_end(fd) != 0) {
     fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
     exit_cleanup(1);
   }
 
   sum_end(file_sum1);
 
   if (remote_version >= 14) {
     read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
     if (verbose > 2)
       fprintf(FERROR,"got file_sum\n");
-    if (memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0)
+    if (fd != -1 && memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0)
       return 0;
   }
   return 1;
 }
 
 
