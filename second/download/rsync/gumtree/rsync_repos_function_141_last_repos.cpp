static void got_flist_entry_status(enum festatus status, int ndx)
{
	struct file_list *flist = flist_for_ndx(ndx, "got_flist_entry_status");

	if (remove_source_files) {
		active_filecnt--;
		active_bytecnt -= F_LENGTH(flist->files[ndx - flist->ndx_start]);
	}

	if (inc_recurse)
		flist->in_progress--;

	switch (status) {
	case FES_SUCCESS:
		if (remove_source_files)
			send_msg_int(MSG_SUCCESS, ndx);
		/* FALL THROUGH */
	case FES_NO_SEND:
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links) {
			struct file_struct *file = flist->files[ndx - flist->ndx_start];
			if (F_IS_HLINKED(file)) {
				if (status == FES_NO_SEND)
					flist_ndx_push(&hlink_list, -2); /* indicates a failure follows */
				flist_ndx_push(&hlink_list, ndx);
				if (inc_recurse)
					flist->in_progress++;
			}
		}
#endif
		break;
	case FES_REDO:
		if (read_batch) {
			if (inc_recurse)
				flist->in_progress++;
			break;
		}
		if (inc_recurse)
			flist->to_redo++;
		flist_ndx_push(&redo_list, ndx);
		break;
	}
}