      }

      if (verbose > 2)
	fprintf(stderr,"recv_files(%s)\n",fname);

      /* open the file */  
      if ((fd1 = open(fname,O_RDONLY)) == -1 &&
	  (fd1 = open(fname,O_RDONLY|O_CREAT,flist->files[i].mode)) == -1) {
	fprintf(stderr,"recv_files failed to open %s\n",fname);
	return -1;
      }

      if (fstat(fd1,&st) != 0) {
	fprintf(stderr,"fstat %s : %s\n",fname,strerror(errno));
	close(fd1);
	return -1;
      }

      if (!S_ISREG(st.st_mode)) {
	fprintf(stderr,"%s : not a regular file\n",fname);
	close(fd1);
	return -1;
      }

      if (st.st_size > 0) {
	buf = map_file(fd1,st.st_size);
	if (!buf) {
	  fprintf(stderr,"map_file failed\n");
	  return -1;
	}
      } else {
