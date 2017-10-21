  if (!flist) {
    fprintf(stderr,"nothing to do\n");
    exit(1);
  }

  if ((pid=fork()) == 0) {
    recv_files(STDIN_FILENO,flist,fname);
    if (verbose > 1)
      fprintf(stderr,"receiver read %d\n",read_total());
    exit(0);
  }

  if (verbose > 2)
    fprintf(stderr,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
    if (S_ISDIR(flist->files[i].mode)) {
      if (dry_run) continue;
      if (mkdir(flist->files[i].name,flist->files[i].mode) != 0 && 
	  errno != EEXIST) {	 
	fprintf(stderr,"mkdir %s: %s\n",
		flist->files[i].name,strerror(errno));
	exit(1);
      }
      continue;
    }
    fname = flist->files[i].name;
    if (flist->count == 1 &&
	argc > 0)
      fname = argv[0];
    recv_generator(fname,flist,i,STDOUT_FILENO);
  }
  write_int(STDOUT_FILENO,-1);
  write_flush(STDOUT_FILENO);
  if (verbose > 1)
    fprintf(stderr,"generator wrote %d\n",write_total());

  waitpid(pid, &status, 0);
  exit(status);
}


static void usage(FILE *f)
