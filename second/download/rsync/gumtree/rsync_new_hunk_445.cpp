	if (!am_server && verbose)
	  printf("%s\n",fname);
	continue;
      }

      if (verbose > 2)
	rprintf(FINFO,"recv_files(%s)\n",fname);

      /* open the file */  
      fd1 = open(fname,O_RDONLY);

      if (fd1 != -1 && do_fstat(fd1,&st) != 0) {
	rprintf(FERROR,"fstat %s : %s\n",fname,strerror(errno));
	receive_data(f_in,NULL,-1,NULL);
	close(fd1);
	continue;
      }

      if (fd1 != -1 && !S_ISREG(st.st_mode)) {
	rprintf(FERROR,"%s : not a regular file (recv_files)\n",fname);
	receive_data(f_in,NULL,-1,NULL);
	close(fd1);
	continue;
      }

      if (fd1 != -1 && st.st_size > 0) {
	buf = map_file(fd1,st.st_size);
	if (verbose > 2)
	  rprintf(FINFO,"recv mapped %s of size %d\n",fname,(int)st.st_size);
      } else {
	buf = NULL;
      }

      /* open tmp file */
      if (tmpdir) {
	      char *f;
	      f = strrchr(fname,'/');
	      if (f == NULL) 
		      f = fname;
	      else 
		      f++;
	      if (strlen(tmpdir)+strlen(f)+10 > MAXPATHLEN) {
		      rprintf(FERROR,"filename too long\n");
		      if (buf) unmap_file(buf);
		      close(fd1);
		      continue;
	      }
	      sprintf(fnametmp,"%s/.%s.XXXXXX",tmpdir,f);
      } else {
	      char *f = strrchr(fname,'/');

	      if (strlen(fname)+9 > MAXPATHLEN) {
		      rprintf(FERROR,"filename too long\n");
		      if (buf) unmap_file(buf);
		      close(fd1);
		      continue;
	      }

	      if (f) {
		      *f = 0;
		      sprintf(fnametmp,"%s/.%s.XXXXXX",fname,f+1);
		      *f = '/';
	      } else {
		      sprintf(fnametmp,".%s.XXXXXX",fname);
	      }
      }
      if (NULL == do_mktemp(fnametmp)) {
	rprintf(FERROR,"mktemp %s failed\n",fnametmp);
	receive_data(f_in,buf,-1,NULL);
	if (buf) unmap_file(buf);
	close(fd1);
	continue;
      }
      fd2 = do_open(fnametmp,O_WRONLY|O_CREAT|O_EXCL,file->mode);
      if (fd2 == -1 && relative_paths && errno == ENOENT && 
	  create_directory_path(fnametmp) == 0) {
	      fd2 = do_open(fnametmp,O_WRONLY|O_CREAT|O_EXCL,file->mode);
      }
      if (fd2 == -1) {
	rprintf(FERROR,"open %s : %s\n",fnametmp,strerror(errno));
	receive_data(f_in,buf,-1,NULL);
	if (buf) unmap_file(buf);
	close(fd1);
	continue;
      }
      
