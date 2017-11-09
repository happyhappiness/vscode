void flist_free(struct file_list *flist)
{
	if (!flist->prev) {
		/* Was FLIST_TEMP dir-list. */
	} else if (flist == flist->prev) {
		first_flist = cur_flist = NULL;
		file_total = 0;
		flist_cnt = 0;
	} else {
		if (flist == cur_flist)
			cur_flist = flist->next;
		if (flist == first_flist)
			first_flist = first_flist->next;
		else {
			flist->prev->next = flist->next;
			if (!flist->next)
				flist->next = first_flist;
		}
		flist->next->prev = flist->prev;
		file_total -= flist->used;
		flist_cnt--;
	}

	if (!flist->prev || !flist_cnt)
		pool_destroy(flist->file_pool);
	else
		pool_free_old(flist->file_pool, flist->pool_boundary);

	if (flist->sorted && flist->sorted != flist->files)
		free(flist->sorted);
	free(flist->files);
	free(flist);
}