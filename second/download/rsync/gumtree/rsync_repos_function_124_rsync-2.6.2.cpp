struct file_list *create_flist_from_batch(void)
{
	char filename[MAXPATHLEN];
	unsigned short flags;
	int i, f, save_pv;
	int64 save_read;

	stringjoin(filename, sizeof filename,
	    batch_prefix, rsync_flist_file, NULL);

	f = do_open(filename, O_RDONLY, 0);
	if (f < 0) {
		rprintf(FERROR, "Batch file %s open error: %s\n",
		    filename, strerror(errno));
		exit_cleanup(1);
	}

	batch_flist = flist_new(WITH_HLINK, "create_flist_from_batch");

	save_read = stats.total_read;
	save_pv = protocol_version;
	protocol_version = read_int(f);

	batch_flist->count = read_int(f);
	flist_expand(batch_flist);

	for (i = 0; (flags = read_byte(f)) != 0; i++) {
		if (protocol_version >= 28 && (flags & XMIT_EXTENDED_FLAGS))
			flags |= read_byte(f) << 8;
		receive_file_entry(&batch_flist->files[i], flags, batch_flist, f);
	}
	receive_file_entry(NULL, 0, NULL, 0); /* Signal that we're done. */

	protocol_version = save_pv;
	stats.total_read = save_read;

	return batch_flist;
}