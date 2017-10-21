      cleanup_fname = fnametmp;

      if (!am_server && verbose)
	printf("%s\n",fname);

      /* recv file data */
      receive_data(f_in,buf,fd2,fname);

      if (fd1 != -1) {
	unmap_file(buf,st.st_size);
	close(fd1);
      }
      close(fd2);

      if (verbose > 2)
	fprintf(FERROR,"renaming %s to %s\n",fnametmp,fname);
