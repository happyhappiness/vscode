struct file_list *flist_new(int flags, char *msg)
{
	struct file_list *flist;

	if (!(flist = new0(struct file_list)))
		out_of_memory(msg);

	if (flags & FLIST_TEMP) {
		if (!(flist->file_pool = pool_create(SMALL_EXTENT, 0,
						     out_of_memory,
						     POOL_INTERN)))
			out_of_memory(msg);
	} else {
		/* This is a doubly linked list with prev looping back to
		 * the end of the list, but the last next pointer is NULL. */
		if (!first_flist) {
			flist->file_pool = pool_create(NORMAL_EXTENT, 0,
						       out_of_memory,
						       POOL_INTERN);
			if (!flist->file_pool)
				out_of_memory(msg);

			flist->ndx_start = flist->flist_num = inc_recurse ? 1 : 0;

			first_flist = cur_flist = flist->prev = flist;
		} else {
			struct file_list *prev = first_flist->prev;

			flist->file_pool = first_flist->file_pool;

			flist->ndx_start = prev->ndx_start + prev->used + 1;
			flist->flist_num = prev->flist_num + 1;

			flist->prev = prev;
			prev->next = first_flist->prev = flist;
		}
		flist->pool_boundary = pool_boundary(flist->file_pool, 0);
		flist_cnt++;
	}

	return flist;
}