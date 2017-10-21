  off_t total=0;
  int i;

  if (verbose > 2)
    fprintf(stderr,"send_files starting\n");

  setup_nonblocking(f_in,f_out);

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) break;

      fname[0] = 0;
      if (flist->files[i].dir) {
	strcpy(fname,flist->files[i].dir);
