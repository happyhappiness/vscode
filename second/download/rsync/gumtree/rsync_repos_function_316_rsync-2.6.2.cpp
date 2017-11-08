void clear_file(int i, struct file_list *flist)
{
	if (flist->hlink_pool && flist->files[i]->link_u.idev)
		pool_free(flist->hlink_pool, 0, flist->files[i]->link_u.idev);
	memset(flist->files[i], 0, file_struct_len);
}