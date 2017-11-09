void increment_active_files(int ndx, int itemizing, enum logcode code)
{
	while (1) {
		/* TODO: tune these limits? */
		int limit = active_bytecnt >= 128*1024 ? 10 : 50;
		if (active_filecnt < limit)
			break;
		check_for_finished_files(itemizing, code, 0);
		if (active_filecnt < limit)
			break;
		wait_for_receiver();
	}

	active_filecnt++;
	active_bytecnt += F_LENGTH(cur_flist->files[ndx - cur_flist->ndx_start]);
}