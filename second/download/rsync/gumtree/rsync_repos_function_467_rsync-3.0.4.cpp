static void start_filelist_progress(char *kind)
{
	rprintf(FCLIENT, "%s ... ", kind);
	if (verbose > 1 || do_progress)
		rprintf(FCLIENT, "\n");
	rflush(FINFO);
}