   n = read_int(f_in);
   remainder = read_int(f_in);
 
   for (i=read_int(f_in); i != 0; i=read_int(f_in)) {
     if (i > 0) {
       if (verbose > 3)
-	fprintf(stderr,"data recv %d at %d\n",i,(int)offset);
+	fprintf(FERROR,"data recv %d at %d\n",i,(int)offset);
 
       if (read_write(f_in,fd,i) != i) {
-	fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
+	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
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
-	fprintf(stderr,"chunk[%d] of size %d at %d offset=%d\n",
+	fprintf(FERROR,"chunk[%d] of size %d at %d offset=%d\n",
 		i,len,(int)offset2,(int)offset);
 
       if (write_sparse(fd,map_ptr(buf,offset2,len),len) != len) {
-	fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
+	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += len;
     }
   }
 
   if (offset > 0 && sparse_end(fd) != 0) {
-    fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
+    fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
     exit_cleanup(1);
   }
 }
 
 
 static void delete_one(struct file_struct *f)
 {
   if (!S_ISDIR(f->mode)) {
     if (!dry_run && unlink(f->name) != 0) {
-      fprintf(stderr,"unlink %s : %s\n",f->name,strerror(errno));
+      fprintf(FERROR,"unlink %s : %s\n",f->name,strerror(errno));
     } else if (verbose) {
-      fprintf(stderr,"deleting %s\n",f->name);
+      fprintf(FERROR,"deleting %s\n",f->name);
     }
   } else {    
     if (!dry_run && rmdir(f->name) != 0) {
       if (errno != ENOTEMPTY)
-	fprintf(stderr,"rmdir %s : %s\n",f->name,strerror(errno));
+	fprintf(FERROR,"rmdir %s : %s\n",f->name,strerror(errno));
     } else if (verbose) {
-      fprintf(stderr,"deleting directory %s\n",f->name);      
+      fprintf(FERROR,"deleting directory %s\n",f->name);      
     }
   }
 }
 
 
 static void delete_files(struct file_list *flist)
