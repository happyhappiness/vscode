void init_hard_links(struct file_list *flist)
{
#if SUPPORT_HARD_LINKS
	int i;

	if (flist->count < 2)
		return;

	if (hlink_list)
		free(hlink_list);

	if (!(hlink_list = new_array(struct file_struct *, flist->count)))
		out_of_memory("init_hard_links");

	hlink_count = 0;
	for (i = 0; i < flist->count; i++) {
		if (flist->files[i]->link_u.idev)
			hlink_list[hlink_count++] = flist->files[i];
	}

	qsort(hlink_list, hlink_count,
	    sizeof hlink_list[0], (int (*)()) hlink_compare);

	if (!hlink_count) {
		free(hlink_list);
		hlink_list = NULL;
	} else
		link_idev_data(flist);
#endif
}