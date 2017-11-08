void write_batch_flist_info(int flist_count, struct file_struct **files)
{
	char filename[MAXPATHLEN];
	int i, f, save_pv;
	int64 save_written;

	stringjoin(filename, sizeof filename,
	    batch_prefix, rsync_flist_file, NULL);

	f = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (f < 0) {
		rprintf(FERROR, "Batch file %s open error: %s\n",
		    filename, strerror(errno));
		exit_cleanup(1);
	}

	save_written = stats.total_written;
	save_pv = protocol_version;
	protocol_version = PROTOCOL_VERSION;
	write_int(f, protocol_version);
	write_int(f, flist_count);

	for (i = 0; i < flist_count; i++) {
		send_file_entry(files[i], f,
		    files[i]->flags & FLAG_TOP_DIR ?  XMIT_TOP_DIR : 0);
	}
	send_file_entry(NULL, f, 0);

	protocol_version = save_pv;
	stats.total_written = save_written;

	close(f);
}