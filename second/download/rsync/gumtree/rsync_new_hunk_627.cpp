}


/*
 * allocate a new file list
 */
struct file_list *flist_new(void)
{
	struct file_list *flist;

	flist = (struct file_list *) malloc(sizeof(flist[0]));
	if (!flist)
		out_of_memory("send_file_list");
