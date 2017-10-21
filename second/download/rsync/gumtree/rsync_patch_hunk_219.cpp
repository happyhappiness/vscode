     if (i > 0) {
       if (verbose > 3)
 	fprintf(FERROR,"data recv %d at %d\n",i,(int)offset);
 
       sum_update(data,i);
 
-      if (write_sparse(fd,data,i) != i) {
+      if (fd != -1 && write_sparse(fd,data,i) != i) {
 	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
 	exit_cleanup(1);
       }
       offset += i;
     } else {
       i = -(i+1);
