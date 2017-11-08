void flist_free(struct file_list *flist)
{
	int i;
	for (i=1;i<flist->count;i++) {
		free_file(flist->files[i]);
		free(flist->files[i]);
	}	
	memset((char *)flist->files, 0, sizeof(flist->files[0])*flist->count);
	free(flist->files);
	memset((char *)flist, 0, sizeof(*flist));
	free(flist);
}