
  if (verbose > 2)
    fprintf(stderr,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
    if (S_ISDIR(flist->files[i].mode)) {
      if (dry_run) continue;
      if (mkdir(flist->files[i].name,flist->files[i].mode) != 0 &&
	  errno != EEXIST) {
	fprintf(stderr,"mkdir %s : %s\n",
		flist->files[i].name,strerror(errno));
