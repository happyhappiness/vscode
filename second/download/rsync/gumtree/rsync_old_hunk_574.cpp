void free_file(struct file_struct *file)
{
	if (!file) return;
	if (file->basename) free(file->basename);
	if (file->link) free(file->link);
	if (file->sum) free(file->sum);
	memset((char *)file, 0, sizeof(*file));
}


/*
 * free up all elements in a flist
 */
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


/*
