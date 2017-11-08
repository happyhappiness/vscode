void check_for_finished_hlinks(int itemizing, enum logcode code)
{
	struct file_struct *file;
	int ndx;

	while ((ndx = get_hlink_num()) != -1) {
		if (ndx < 0 || ndx >= the_file_list->count)
			continue;

		file = the_file_list->files[ndx];
		if (!file->link_u.links)
			continue;

		hard_link_cluster(file, ndx, itemizing, code);
	}
}