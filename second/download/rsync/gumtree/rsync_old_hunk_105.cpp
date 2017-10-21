	fprintf(stderr,"fstat failed : %s\n",strerror(errno));
	return -1;
      }
      
      if (st.st_size > 0) {
	buf = map_file(fd,st.st_size);
	if (!buf) {
	  fprintf(stderr,"map_file failed : %s\n",strerror(errno));	  
	  return -1;
	}
      } else {
	buf = NULL;
      }

      if (verbose > 2)
	fprintf(stderr,"send_files mapped %s of size %d\n",
