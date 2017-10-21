 	close(fd1);
 	return -1;
       }
 
       if (fd1 != -1 && st.st_size > 0) {
 	buf = map_file(fd1,st.st_size);
+	if (verbose > 2)
+	  fprintf(FERROR,"recv mapped %s of size %d\n",fname,(int)st.st_size);
       } else {
 	buf = NULL;
       }
 
-      if (verbose > 2)
-	fprintf(FERROR,"mapped %s of size %d\n",fname,(int)st.st_size);
-
       /* open tmp file */
       sprintf(fnametmp,"%s.XXXXXX",fname);
       if (NULL == mktemp(fnametmp)) {
 	fprintf(FERROR,"mktemp %s failed\n",fnametmp);
 	return -1;
       }
