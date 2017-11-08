int get_redo_num(int itemizing, enum logcode code)
{
	while (1) {
		if (hlink_list.head)
			check_for_finished_hlinks(itemizing, code);
		if (redo_list.head)
			break;
		read_msg_fd();
	}

	return flist_ndx_pop(&redo_list);
}