 	  printf("%s\n",fname);
 	write_int(f_out,i);
 	continue;
       }
 
       s = receive_sums(f_in);
-      if (!s) 
+      if (!s) {
+	fprintf(stderr,"receive_sums failed\n");
 	return -1;
+      }
 
       fd = open(fname,O_RDONLY);
       if (fd == -1) {
 	fprintf(stderr,"send_files failed to open %s: %s\n",
 		fname,strerror(errno));
 	continue;
       }
   
       /* map the local file */
-      if (fstat(fd,&st) != 0) 
+      if (fstat(fd,&st) != 0) {
+	fprintf(stderr,"fstat failed : %s\n",strerror(errno));
 	return -1;
+      }
       
       if (st.st_size > 0) {
 	buf = map_file(fd,st.st_size);
-	if (!buf) return -1;
+	if (!buf) {
+	  fprintf(stderr,"map_file failed : %s\n",strerror(errno));	  
+	  return -1;
+	}
       } else {
 	buf = NULL;
       }
 
       if (verbose > 2)
 	fprintf(stderr,"send_files mapped %s of size %d\n",
