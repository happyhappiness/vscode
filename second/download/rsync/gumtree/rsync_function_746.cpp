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