void increment_active_files(int ndx, int itemizing, enum logcode code)
{
	/* TODO: tune these limits? */
	while (active_filecnt >= (active_bytecnt >= 128*1024 ? 10 : 50)) {
		if (hlink_list.head)
			check_for_finished_hlinks(itemizing, code);
		read_msg_fd();
	}

	active_filecnt++;
	active_bytecnt += the_file_list->files[ndx]->length;
}