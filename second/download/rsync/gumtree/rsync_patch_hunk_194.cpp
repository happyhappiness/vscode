 	len = remainder;
 
       if (verbose > 3)
 	fprintf(FERROR,"chunk[%d] of size %d at %d offset=%d\n",
 		i,len,(int)offset2,(int)offset);
 
-      if (write_sparse(fd,map_ptr(buf,offset2,len),len) != len) {
+      map = map_ptr(buf,offset2,len);
+
+      see_token(map, len);
+      sum_update(map,len);
+
+      if (write_sparse(fd,map,len) != len) {
 	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += len;
     }
   }
 
   if (offset > 0 && sparse_end(fd) != 0) {
     fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
     exit_cleanup(1);
   }
+
+  sum_end(file_sum1);
+
+  if (remote_version >= 14) {
+    read_buf(f_in,file_sum2,SUM_LENGTH);
+    if (verbose > 2)
+      fprintf(FERROR,"got file_sum\n");
+    if (memcmp(file_sum1,file_sum2,SUM_LENGTH) != 0)
+      return 0;
+  }
+  return 1;
 }
 
 
 static void delete_one(struct file_struct *f)
 {
   if (!S_ISDIR(f->mode)) {
