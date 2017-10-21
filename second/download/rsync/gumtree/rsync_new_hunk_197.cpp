      cleanup_fname = fnametmp;

      if (!am_server && verbose)
	printf("%s\n",fname);

      /* recv file data */
      recv_ok = receive_data(f_in,buf,fd2,fname);

      if (fd1 != -1) {
	if (buf) unmap_file(buf);
	close(fd1);
      }
      close(fd2);

      if (verbose > 2)
	fprintf(FERROR,"renaming %s to %s\n",fnametmp,fname);
