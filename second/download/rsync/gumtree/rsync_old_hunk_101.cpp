    fprintf(stderr,"failed to open %s : %s\n",fname,strerror(errno));
    return;
  }

  if (st.st_size > 0) {
    buf = map_file(fd,st.st_size);
    if (!buf) {
      fprintf(stderr,"mmap : %s\n",strerror(errno));
      close(fd);
      return;
    }
  } else {
    buf = NULL;
  }

  if (verbose > 3)
    fprintf(stderr,"mapped %s of size %d\n",fname,(int)st.st_size);
