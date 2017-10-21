  for (i=0;i<flist->count;i++) {
    clean_fname(flist->files[i].name);
  }
      
  qsort(flist->files,flist->count,
	sizeof(flist->files[0]),
	(int (*)())flist_compare);

  for (i=1;i<flist->count;i++) {
    if (flist->files[i].name &&
	strcmp(flist->files[i].name,flist->files[i-1].name) == 0) {
      if (verbose > 1 && !am_server)
	fprintf(stderr,"removing duplicate name %s from file list\n",
		flist->files[i].name);
      free(flist->files[i-1].name);
      flist->files[i-1].name = NULL;
    }
  }
}

