static void maybe_emit_filelist_progress(int count)
{
	if (INFO_GTE(FLIST, 2) && show_filelist_p() && (count % 100) == 0)
		emit_filelist_progress(count);
}