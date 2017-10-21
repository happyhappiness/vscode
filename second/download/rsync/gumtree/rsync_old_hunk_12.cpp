      sprintf(fnametmp,"%s.XXXXXX",fname);
      if (NULL == mktemp(fnametmp)) 
	return -1;
      fd2 = open(fnametmp,O_WRONLY|O_CREAT,st.st_mode);
      if (fd2 == -1) return -1;

      if (verbose)
	fprintf(stderr,"%s\n",fname);

      /* recv file data */
      receive_data(f_in,buf,fd2);

      close(fd1);
      close(fd2);
