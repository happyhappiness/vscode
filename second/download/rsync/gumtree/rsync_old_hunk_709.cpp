
	if (file_compare(&flist->files[flist_up(flist, low)], &f) == 0)
		return flist_up(flist, low);
	return -1;
}


/*
 * free up one file
 */
void free_file(struct file_struct *file)
{
	if (!file)
		return;
	if (file->basename)
		free(file->basename);
	if (file->link)
		free(file->link);
	if (file->sum)
		free(file->sum);
	*file = null_file;
}


/*
 * allocate a new file list
 */
struct file_list *flist_new(void)
{
	struct file_list *flist;

	flist = new(struct file_list);
	if (!flist)
		out_of_memory("send_file_list");

	flist->count = 0;
	flist->malloced = 0;
	flist->files = NULL;

#if ARENA_SIZE > 0
	flist->string_area = string_area_new(0);
#else
	flist->string_area = NULL;
#endif
	return flist;
}

/*
 * free up all elements in a flist
 */
