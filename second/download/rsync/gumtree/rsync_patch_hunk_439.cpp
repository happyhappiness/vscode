 
   sum_init();
 
   for (i=recv_token(f_in,&data); i != 0; i=recv_token(f_in,&data)) {
     if (i > 0) {
       if (verbose > 3)
-	fprintf(FINFO,"data recv %d at %d\n",i,(int)offset);
+	rprintf(FINFO,"data recv %d at %d\n",i,(int)offset);
 
       sum_update(data,i);
 
       if (fd != -1 && write_file(fd,data,i) != i) {
-	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
+	rprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += i;
     } else {
       i = -(i+1);
       offset2 = i*n;
       len = n;
       if (i == count-1 && remainder != 0)
 	len = remainder;
 
       if (verbose > 3)
-	fprintf(FINFO,"chunk[%d] of size %d at %d offset=%d\n",
+	rprintf(FINFO,"chunk[%d] of size %d at %d offset=%d\n",
 		i,len,(int)offset2,(int)offset);
 
       map = map_ptr(buf,offset2,len);
 
       see_token(map, len);
       sum_update(map,len);
 
       if (fd != -1 && write_file(fd,map,len) != len) {
-	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
+	rprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += len;
     }
   }
 
   if (fd != -1 && offset > 0 && sparse_end(fd) != 0) {
-    fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
+    rprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
     exit_cleanup(1);
   }
 
   sum_end(file_sum1);
 
   if (remote_version >= 14) {
     read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
     if (verbose > 2)
-      fprintf(FINFO,"got file_sum\n");
+      rprintf(FINFO,"got file_sum\n");
     if (fd != -1 && memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0)
       return 0;
   }
   return 1;
 }
 
 
 static void delete_one(struct file_struct *f)
 {
   if (!S_ISDIR(f->mode)) {
     if (do_unlink(f_name(f)) != 0) {
-      fprintf(FERROR,"unlink %s : %s\n",f_name(f),strerror(errno));
+      rprintf(FERROR,"unlink %s : %s\n",f_name(f),strerror(errno));
     } else if (verbose) {
-      fprintf(FINFO,"deleting %s\n",f_name(f));
+      rprintf(FINFO,"deleting %s\n",f_name(f));
     }
   } else {    
     if (do_rmdir(f_name(f)) != 0) {
       if (errno != ENOTEMPTY && errno != EEXIST)
-	fprintf(FERROR,"rmdir %s : %s\n",f_name(f),strerror(errno));
+	rprintf(FERROR,"rmdir %s : %s\n",f_name(f),strerror(errno));
     } else if (verbose) {
-      fprintf(FINFO,"deleting directory %s\n",f_name(f));      
+      rprintf(FINFO,"deleting directory %s\n",f_name(f));      
     }
   }
 }
 
 
 
