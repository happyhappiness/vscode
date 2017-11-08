static void maybe_emit_filelist_progress(const struct file_list *flist)
{
	if (do_progress && show_filelist_p() && ((flist->count % 100) == 0))
		emit_filelist_progress(flist);
}