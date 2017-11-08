void clear_file(struct file_struct *file, struct file_list *flist)
{
	if (flist->hlink_pool && file->link_u.idev)
		pool_free(flist->hlink_pool, 0, file->link_u.idev);
	memset(file, 0, file_struct_len);
	/* In an empty entry, dir.depth is an offset to the next non-empty
	 * entry.  Likewise for length in the opposite direction.  We assume
	 * that we're alone for now since flist_find() will adjust the counts
	 * it runs into that aren't up-to-date. */
	file->length = file->dir.depth = 1;
}