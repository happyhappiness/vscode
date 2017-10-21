void init_hard_links(void)
{
#ifdef SUPPORT_HARD_LINKS
	int i;

	if (hlink_list)
		free(hlink_list);

	if (!(hlink_list = new_array(int32, the_file_list->count)))
		out_of_memory("init_hard_links");

	hlink_count = 0;
	for (i = 0; i < the_file_list->count; i++) {
		if (FPTR(i)->link_u.idev)
			hlink_list[hlink_count++] = i;
	}

	qsort(hlink_list, hlink_count,
	    sizeof hlink_list[0], (int (*)()) hlink_compare);

	if (!hlink_count) {
		free(hlink_list);
		hlink_list = NULL;
	} else
		link_idev_data();
#endif
}