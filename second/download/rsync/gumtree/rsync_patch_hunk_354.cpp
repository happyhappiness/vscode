 	continue;
       }
 
       if (fd1 != -1 && st.st_size > 0) {
 	buf = map_file(fd1,st.st_size);
 	if (verbose > 2)
-	  fprintf(FERROR,"recv mapped %s of size %d\n",fname,(int)st.st_size);
+	  fprintf(FINFO,"recv mapped %s of size %d\n",fname,(int)st.st_size);
       } else {
 	buf = NULL;
       }
 
       /* open tmp file */
       if (strlen(fname) > (MAXPATHLEN-8)) {
 	fprintf(FERROR,"filename too long\n");
+	if (buf) unmap_file(buf);
 	close(fd1);
 	continue;
       }
       if (tmpdir) {
 	      char *f;
 	      f = strrchr(fname,'/');
