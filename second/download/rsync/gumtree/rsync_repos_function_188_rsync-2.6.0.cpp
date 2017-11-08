void log_exit(int code, const char *file, int line)
{
	if (code == 0) {
		extern struct stats stats;		
		rprintf(FLOG,"wrote %.0f bytes  read %.0f bytes  total size %.0f\n",
			(double)stats.total_written,
			(double)stats.total_read,
			(double)stats.total_size);
	} else {
		const char *name;

		name = rerr_name(code);
		if (!name)
			name = "unexplained error";

		/* VANISHED is not an error, only a warning */
		if (code == RERR_VANISHED) {
			rprintf(FINFO, "rsync warning: %s (code %d) at %s(%d)\n", 
				name, code, file, line);
		} else {
			rprintf(FERROR, "rsync error: %s (code %d) at %s(%d)\n",
				name, code, file, line);
		}
	}
}