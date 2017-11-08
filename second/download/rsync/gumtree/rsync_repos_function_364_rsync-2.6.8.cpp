void flist_free(struct file_list *flist)
{
	pool_destroy(flist->file_pool);
	pool_destroy(flist->hlink_pool);
	free(flist->files);
	free(flist);
}