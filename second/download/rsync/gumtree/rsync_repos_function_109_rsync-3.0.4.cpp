void increment_active_files(int ndx, int itemizing, enum logcode code)
{
	/* TODO: tune these limits? */
	while (active_filecnt >= (active_bytecnt >= 128*1024 ? 10 : 50)) {
		check_for_finished_files(itemizing, code, 0);
		if (iobuf_out_cnt)
			io_flush(NORMAL_FLUSH);
		else
			read_msg_fd();
	}

	active_filecnt++;
	active_bytecnt += F_LENGTH(cur_flist->files[ndx - cur_flist->ndx_start]);
}