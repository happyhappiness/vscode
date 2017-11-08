static void start_filelist_progress(char *kind)
{
	rprintf(FINFO, "%s ... ", kind);
	if ((verbose > 1) || do_progress)
		rprintf(FINFO, "\n");
	rflush(FINFO);
}