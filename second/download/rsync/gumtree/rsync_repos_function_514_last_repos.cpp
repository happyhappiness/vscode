static void emit_filelist_progress(int count)
{
	rprintf(FCLIENT, " %d files...\r", count);
}