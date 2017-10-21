void clean_flist(struct file_list *flist)
{
  int i;

  if (!flist || flist->count == 0) 
    return;
  
  for (i=0;i<flist->count;i++) {
    clean_fname(flist->files[i].name);
  }
      
  qsort(flist->files,flist->count,
	sizeof(flist->files[0]),
	(int (*)())file_compare);

  for (i=1;i<flist->count;i++) {
    if (flist->files[i].name &&
	strcmp(flist->files[i].name,flist->files[i-1].name) == 0) {
      if (verbose > 1 && !am_server)
	fprintf(FERROR,"removing duplicate name %s from file list %d\n",
		flist->files[i-1].name,i-1);
      free(flist->files[i-1].name);
      bzero((char *)&flist->files[i-1],sizeof(flist->files[i-1]));
    } 
  }
}