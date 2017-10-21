 
   sum_end(file_sum);
 
   if (remote_version >= 14) {
     if (verbose > 2)
       fprintf(FERROR,"sending file_sum\n");
-    write_buf(f,file_sum,SUM_LENGTH);
+    write_buf(f,file_sum,MD4_SUM_LENGTH);
   }
 
   if (targets) {
     free(targets);
     targets=NULL;
   }
