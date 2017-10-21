      if (!am_server && verbose)
	printf("%s\n",fname);

      /* recv file data */
      recv_ok = receive_data(f_in,buf,fd2,fname);

      if (buf) unmap_file(buf);
      if (fd1 != -1) {
	close(fd1);
      }
      close(fd2);

      if (verbose > 2)
	fprintf(FINFO,"renaming %s to %s\n",fnametmp,fname);

      if (make_backups) {
	char fnamebak[MAXPATHLEN];
	if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
		fprintf(FERROR,"backup filename too long\n");
		continue;
