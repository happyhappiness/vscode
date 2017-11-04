void match_hard_links(struct file_list *flist)
{
	if (!list_only) {
		int i, ndx_count = 0;
		int32 *ndx_list;

		if (!(ndx_list = new_array(int32, flist->used)))
			out_of_memory("match_hard_links");

		for (i = 0; i < flist->used; i++) {
			if (F_IS_HLINKED(flist->sorted[i]))
				ndx_list[ndx_count++] = i;
		}

		hlink_flist = flist;

		if (ndx_count)
			match_gnums(ndx_list, ndx_count);

		free(ndx_list);
	}
	if (protocol_version < 30)
		idev_destroy();
}