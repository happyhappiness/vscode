struct file_list *recv_file_list(int f)
{
	struct file_list *flist;
	unsigned char flags;
	int64 start_read;
	extern int list_only;

	if (show_filelist_p())
		start_filelist_progress("receiving file list");

	start_read = stats.total_read;

	flist = (struct file_list *) malloc(sizeof(flist[0]));
	if (!flist)
		goto oom;

	flist->count = 0;
	flist->malloced = 1000;
	flist->files =
	    (struct file_struct **) malloc(sizeof(flist->files[0]) *
					   flist->malloced);
	if (!flist->files)
		goto oom;


	for (flags = read_byte(f); flags; flags = read_byte(f)) {
		int i = flist->count;
		
		flist_expand(flist);

		receive_file_entry(&flist->files[i], flags, f);

		if (S_ISREG(flist->files[i]->mode))
			stats.total_size += flist->files[i]->length;

		flist->count++;

		maybe_emit_filelist_progress(flist);

		if (verbose > 2)
			rprintf(FINFO, "recv_file_name(%s)\n",
				f_name(flist->files[i]));
	}


	if (verbose > 2)
		rprintf(FINFO, "received %d names\n", flist->count);

	clean_flist(flist, relative_paths);

	if (show_filelist_p()) {
		finish_filelist_progress(flist);
	}

	/* now recv the uid/gid list. This was introduced in protocol version 15 */
	if (f != -1 && remote_version >= 15) {
		recv_uid_list(f, flist);
	}

	/* if protocol version is >= 17 then recv the io_error flag */
	if (f != -1 && remote_version >= 17 && !read_batch) {	/* dw-added readbatch */
		extern int module_id;
		extern int ignore_errors;
		if (lp_ignore_errors(module_id) || ignore_errors) {
			read_int(f);
		} else {
			io_error |= read_int(f);
		}
	}

	if (list_only) {
		int i;
		for (i = 0; i < flist->count; i++) {
			list_file_entry(flist->files[i]);
		}
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