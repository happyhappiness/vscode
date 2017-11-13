void send_extra_file_list(int f, int at_least)
{
	struct file_list *flist;
	int64 start_write;
	uint16 prev_flags;
	int old_cnt, save_io_error = io_error;

	if (flist_eof)
		return;

	/* Keep sending data until we have the requested number of
	 * files in the upcoming file-lists. */
	old_cnt = cur_flist->used;
	for (flist = first_flist; flist != cur_flist; flist = flist->next)
		old_cnt += flist->used;
	while (file_total - old_cnt < at_least) {
		struct file_struct *file = dir_flist->sorted[send_dir_ndx];
		int dir_ndx, dstart = dir_count;
		const char *pathname = F_PATHNAME(file);
		int32 *dp;

		flist = flist_new(0, "send_extra_file_list");
		start_write = stats.total_written;

		if (unsort_ndx)
			dir_ndx = F_NDX(file);
		else
			dir_ndx = send_dir_ndx;
		write_ndx(f, NDX_FLIST_OFFSET - dir_ndx);
		flist->parent_ndx = dir_ndx;

		send1extra(f, file, flist);
		prev_flags = file->flags;
		dp = F_DIR_NODE_P(file);

		/* If there are any duplicate directory names that follow, we
		 * send all the dirs together in one file-list.  The dir_flist
		 * tree links all the child subdirs onto the last dup dir. */
		while ((dir_ndx = DIR_NEXT_SIBLING(dp)) >= 0
		    && dir_flist->sorted[dir_ndx]->flags & FLAG_DUPLICATE) {
			send_dir_ndx = dir_ndx;
			file = dir_flist->sorted[dir_ndx];
			/* Try to avoid some duplicate scanning of identical dirs. */
			if (F_PATHNAME(file) == pathname && prev_flags & FLAG_CONTENT_DIR)
				file->flags &= ~FLAG_CONTENT_DIR;
			send1extra(f, file, flist);
			prev_flags = file->flags;
			dp = F_DIR_NODE_P(file);
		}

		write_byte(f, 0);

		if (need_unsorted_flist) {
			if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
				out_of_memory("send_extra_file_list");
			memcpy(flist->sorted, flist->files,
			       flist->used * sizeof (struct file_struct*));
		} else
			flist->sorted = flist->files;

		flist_sort_and_clean(flist, 0);

		add_dirs_to_tree(send_dir_ndx, flist, dir_count - dstart);
		flist_done_allocating(flist);

		file_total += flist->used;
		stats.flist_size += stats.total_written - start_write;
		stats.num_files += flist->used;
		if (verbose > 3)
			output_flist(flist);

		if (DIR_FIRST_CHILD(dp) >= 0) {
			send_dir_ndx = DIR_FIRST_CHILD(dp);
			send_dir_depth++;
		} else {
			while (DIR_NEXT_SIBLING(dp) < 0) {
				if ((send_dir_ndx = DIR_PARENT(dp)) < 0) {
					write_ndx(f, NDX_FLIST_EOF);
					flist_eof = 1;
					change_local_filter_dir(NULL, 0, 0);
					goto finish;
				}
				send_dir_depth--;
				file = dir_flist->sorted[send_dir_ndx];
				dp = F_DIR_NODE_P(file);
			}
			send_dir_ndx = DIR_NEXT_SIBLING(dp);
		}
	}

  finish:
	if (io_error != save_io_error && !ignore_errors)
		send_msg_int(MSG_IO_ERROR, io_error);
}