     if (i > 0) {
       if (verbose > 3)
 	fprintf(stderr,"data recv %d at %d\n",i,(int)offset);
 
       if (read_write(f_in,fd,i) != i) {
 	fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
-	exit(1);
+	exit_cleanup(1);
       }
       offset += i;
     } else {
       i = -(i+1);
       offset2 = i*n;
       len = n;
