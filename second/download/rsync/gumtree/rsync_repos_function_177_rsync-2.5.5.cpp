void log_transfer(struct file_struct *file, const char *fname)
{
	extern int verbose;

	if (!verbose) return;

	rprintf(FINFO, "%s\n", fname);
}