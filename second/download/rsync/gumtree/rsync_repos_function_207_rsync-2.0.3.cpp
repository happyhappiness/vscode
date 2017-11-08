void flist_free(struct file_list *flist)
{
	int i;
	for (i=1;i<flist->count;i++) {
		free_file(flist->files[i]);
		free(flist->files[i]);
	}	
	bzero((char *)flist->files, sizeof(flist->files[0])*flist->count);
	free(flist->files);
	bzero((char *)flist, sizeof(*flist));
	free(flist);
}