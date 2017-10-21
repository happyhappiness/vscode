 	continue;
       }
   
       /* map the local file */
       if (fstat(fd,&st) != 0) {
 	fprintf(FERROR,"fstat failed : %s\n",strerror(errno));
+	close(fd);
 	return -1;
       }
       
       if (st.st_size > 0) {
 	buf = map_file(fd,st.st_size);
       } else {
