static void flist_done_allocating(struct file_list *flist)
{
	void *ptr = pool_boundary(flist->file_pool, 8*1024);
	if (flist->pool_boundary == ptr)
		flist->pool_boundary = NULL; /* list didn't use any pool memory */
	else
		flist->pool_boundary = ptr;
}