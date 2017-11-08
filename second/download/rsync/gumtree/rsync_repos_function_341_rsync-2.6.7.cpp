static void emit_filelist_progress(int count)
{
	rprintf(FINFO, " %d files...\r", count);
}