	close(fd1);
	return -1;
      }

      if (fd1 != -1 && st.st_size > 0) {
	buf = map_file(fd1,st.st_size);
      } else {
	buf = NULL;
      }

      if (verbose > 2)
	fprintf(stderr,"mapped %s of size %d\n",fname,(int)st.st_size);
