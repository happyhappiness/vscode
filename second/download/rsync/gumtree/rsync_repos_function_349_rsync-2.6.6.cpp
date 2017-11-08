struct file_list *recv_file_list(int f)
{
	struct file_list *flist;
	unsigned short flags;
	int64 start_read;

	if (show_filelist_p())
		start_filelist_progress("receiving file list");

	start_read = stats.total_read;

	flist = flist_new(WITH_HLINK, "recv_file_list");

	flist->count = 0;
	flist->malloced = 1000;
	flist->files = new_array(struct file_struct *, flist->malloced);
	if (!flist->files)
		goto oom;


	while ((flags = read_byte(f)) != 0) {
		struct file_struct *file;

		flist_expand(flist);

		if (protocol_version >= 28 && (flags & XMIT_EXTENDED_FLAGS))
			flags |= read_byte(f) << 8;
		file = receive_file_entry(flist, flags, f);

		if (S_ISREG(file->mode))
			stats.total_size += file->length;

		flist->files[flist->count++] = file;

		maybe_emit_filelist_progress(flist->count);

		if (verbose > 2) {
			rprintf(FINFO, "recv_file_name(%s)\n",
				safe_fname(f_name(file)));
		}
	}
	receive_file_entry(NULL, 0, 0); /* Signal that we're done. */

	if (verbose > 2)
		rprintf(FINFO, "received %d names\n", flist->count);

	if (show_filelist_p())
		finish_filelist_progress(flist);

	clean_flist(flist, relative_paths, 1);

	if (f >= 0) {
		/* Now send the uid/gid list. This was introduced in
		 * protocol version 15 */
		recv_uid_list(f, flist);

		/* Recv the io_error flag */
		if (lp_ignore_errors(module_id) || ignore_errors)
			read_int(f);
		else
			io_error |= read_int(f);
	}

	if (verbose > 3)
		output_flist(flist);

	if (list_only) {
		int i;
		for (i = 0; i < flist->count; i++)
			list_file_entry(flist->files[i]);
	}

	if (verbose > 2)
		rprintf(FINFO, "recv_file_list done\n");

	stats.flist_size = stats.total_read - start_read;
	stats.num_files = flist->count;

	return flist;

oom:
	out_of_memory("recv_file_list");
	return NULL;		/* not reached */
}