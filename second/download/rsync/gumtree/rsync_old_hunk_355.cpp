	fprintf(FERROR,"mktemp %s failed\n",fnametmp);
	receive_data(f_in,buf,-1,NULL);
	if (buf) unmap_file(buf);
	close(fd1);
	continue;
      }
      fd2 = open(fnametmp,O_WRONLY|O_CREAT|O_EXCL,file->mode);
      if (fd2 == -1 && relative_paths && errno == ENOENT && 
	  create_directory_path(fnametmp) == 0) {
	      fd2 = open(fnametmp,O_WRONLY|O_CREAT|O_EXCL,file->mode);
      }
      if (fd2 == -1) {
	fprintf(FERROR,"open %s : %s\n",fnametmp,strerror(errno));
	receive_data(f_in,buf,-1,NULL);
	if (buf) unmap_file(buf);
	close(fd1);
