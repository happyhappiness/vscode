static void start_filelist_progress(char *kind)
{
	rprintf(FCLIENT, "%s ... ", kind);
	output_needs_newline = 1;
	rflush(FINFO);
}