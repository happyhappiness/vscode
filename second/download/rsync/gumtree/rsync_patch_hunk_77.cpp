       if (!am_server && verbose)
 	printf("%s\n",fname);
 
       /* recv file data */
       receive_data(f_in,buf,fd2,fname);
 
-      if (fd1 != -1) close(fd1);
+      if (fd1 != -1) {
+	unmap_file(buf,st.st_size);
+	close(fd1);
+      }
       close(fd2);
 
       if (verbose > 2)
 	fprintf(stderr,"renaming %s to %s\n",fnametmp,fname);
 
       if (make_backups) {
