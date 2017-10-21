    if (i > 0) {
      if (verbose > 3)
	fprintf(FINFO,"data recv %d at %d\n",i,(int)offset);

      sum_update(data,i);

      if (fd != -1 && write_file(fd,data,i) != i) {
	fprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
	exit_cleanup(1);
      }
      offset += i;
    } else {
      i = -(i+1);
