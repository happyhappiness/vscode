       }
 
       /* open tmp file */
       sprintf(fnametmp,"%s.XXXXXX",fname);
       if (NULL == mktemp(fnametmp)) {
 	fprintf(FERROR,"mktemp %s failed\n",fnametmp);
-	return -1;
+	receive_data(f_in,buf,-1,NULL);
+	if (buf) unmap_file(buf);
+	close(fd1);
+	continue;
       }
       fd2 = open(fnametmp,O_WRONLY|O_CREAT,file->mode);
       if (fd2 == -1) {
 	fprintf(FERROR,"open %s : %s\n",fnametmp,strerror(errno));
-	return -1;
+	receive_data(f_in,buf,-1,NULL);
+	if (buf) unmap_file(buf);
+	close(fd1);
+	continue;
       }
       
       cleanup_fname = fnametmp;
 
       if (!am_server && verbose)
 	printf("%s\n",fname);
