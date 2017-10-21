       }
 
       if (verbose > 2)
 	fprintf(stderr,"recv_files(%s)\n",fname);
 
       /* open the file */  
-      fd1 = open(fname,O_RDONLY|O_CREAT,flist->files[i].mode);
-
-      if (fd1 == -1) {
+      if ((fd1 = open(fname,O_RDONLY)) == -1 &&
+	  (fd1 = open(fname,O_RDONLY|O_CREAT,flist->files[i].mode)) == -1) {
 	fprintf(stderr,"recv_files failed to open %s\n",fname);
 	return -1;
       }
 
       if (fstat(fd1,&st) != 0) {
 	fprintf(stderr,"fstat %s : %s\n",fname,strerror(errno));
