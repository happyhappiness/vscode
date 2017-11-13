void clean_flist(struct file_list *flist)
{
	int i;

	if (!flist || flist->count == 0) 
		return;
  
	qsort(flist->files,flist->count,
	      sizeof(flist->files[0]),
	      (int (*)())file_compare);

	for (i=1;i<flist->count;i++) {
		if (flist->files[i]->basename &&
		    flist->files[i-1]->basename &&
		    strcmp(f_name(flist->files[i]),
			   f_name(flist->files[i-1])) == 0) {
			if (verbose > 1 && !am_server)
				fprintf(FINFO,"removing duplicate name %s from file list %d\n",
					f_name(flist->files[i-1]),i-1);
			free_file(flist->files[i]);
		} 
	}
}