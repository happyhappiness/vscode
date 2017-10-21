  int i;

  if (verbose > 2)
    fprintf(stderr,"recv_files(%d) starting\n",flist->count);

  if (recurse && delete_mode && !local_name && flist->count>0) {
    delete_files(flist);
  }

  while (1) 
    {
      i = read_int(f_in);
