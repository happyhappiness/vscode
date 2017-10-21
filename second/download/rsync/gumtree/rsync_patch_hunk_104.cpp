       /* open tmp file */
       sprintf(fnametmp,"%s.XXXXXX",fname);
       if (NULL == mktemp(fnametmp)) {
 	fprintf(stderr,"mktemp %s failed\n",fnametmp);
 	return -1;
       }
-      fd2 = open(fnametmp,O_WRONLY|O_CREAT,st.st_mode);
+      fd2 = open(fnametmp,O_WRONLY|O_CREAT,flist->files[i].mode);
       if (fd2 == -1) {
 	fprintf(stderr,"open %s : %s\n",fnametmp,strerror(errno));
 	return -1;
       }
       
       cleanup_fname = fnametmp;
