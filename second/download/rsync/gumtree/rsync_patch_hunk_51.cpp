 	close(fd1);
 	return -1;
       }
 
       if (st.st_size > 0) {
 	buf = map_file(fd1,st.st_size);
-	if (!buf) return -1;
+	if (!buf) {
+	  fprintf(stderr,"map_file failed\n");
+	  return -1;
+	}
       } else {
 	buf = NULL;
       }
 
       if (verbose > 2)
 	fprintf(stderr,"mapped %s of size %d\n",fname,(int)st.st_size);
 
       /* open tmp file */
       sprintf(fnametmp,"%s.XXXXXX",fname);
-      if (NULL == mktemp(fnametmp)) 
+      if (NULL == mktemp(fnametmp)) {
+	fprintf(stderr,"mktemp %s failed\n",fnametmp);
 	return -1;
+      }
       fd2 = open(fnametmp,O_WRONLY|O_CREAT,st.st_mode);
-      if (fd2 == -1) return -1;
+      if (fd2 == -1) {
+	fprintf(stderr,"open %s : %s\n",fnametmp,strerror(errno));
+	return -1;
+      }
 
       if (!am_server && verbose)
 	printf("%s\n",fname);
 
       /* recv file data */
       receive_data(f_in,buf,fd2);
