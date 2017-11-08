static void emit_filelist_progress(const struct file_list *flist)
{
	rprintf(FINFO, " %d files...\r", flist->count);
}