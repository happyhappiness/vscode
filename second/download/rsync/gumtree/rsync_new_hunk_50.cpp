  char *buf;
  int i;

  if (verbose > 2)
    fprintf(stderr,"recv_files(%d) starting\n",flist->count);

  if (recurse && delete_mode && !local_name && flist->count>0) {
    if (cvs_exclude)
      add_cvs_excludes();
    delete_files(flist);
  }

  while (1) 
    {
      i = read_int(f_in);
      if (i == -1) break;

      fname = flist->files[i].name;
