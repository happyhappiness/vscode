void write_batch_flist_info(int flist_count, struct file_struct **fptr)
{
	int i;
	int bytes_to_write;

	/* Write flist info to batch file */

	bytes_to_write =
	    sizeof(unsigned) +
	    sizeof(time_t) +
	    sizeof(OFF_T) +
	    sizeof(mode_t) +
	    sizeof(INO64_T) +
	    sizeof(DEV64_T) +
	    sizeof(DEV64_T) +
	    sizeof(uid_t) +
	    sizeof(gid_t);

	fdb_open = 1;
	fdb_close = 0;

	for (i = 0; i < flist_count; i++) {
		write_batch_flist_file((char *) fptr[i], bytes_to_write);
		write_char_bufs(fptr[i]->basename);
		write_char_bufs(fptr[i]->dirname);
		write_char_bufs(fptr[i]->basedir);
		write_char_bufs(fptr[i]->link);
		if (i == flist_count - 1) {
			fdb_close = 1;
		}
		write_char_bufs(fptr[i]->sum);
	}
}