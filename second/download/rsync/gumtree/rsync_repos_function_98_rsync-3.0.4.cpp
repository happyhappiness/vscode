static void got_flist_entry_status(enum festatus status, const char *buf)
{
	int ndx = IVAL(buf, 0);
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
			send_msg(MSG_SUCCESS, buf, 4, 0);
		if (preserve_hard_links) {
			struct file_struct *file = flist->files[ndx - flist->ndx_start];
			if (F_IS_HLINKED(file)) {
				flist_ndx_push(&hlink_list, ndx);
				flist->in_progress++;
			}
		}
		break;
	case FES_REDO:
		if (inc_recurse)
			flist->to_redo++;
		flist_ndx_push(&redo_list, ndx);
		break;
	case FES_NO_SEND:
		break;
	}
}