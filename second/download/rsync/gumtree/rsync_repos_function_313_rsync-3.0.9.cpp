void log_exit(int code, const char *file, int line)
{
	if (code == 0) {
		rprintf(FLOG,"sent %.0f bytes  received %.0f bytes  total size %.0f\n",
			(double)stats.total_written,
			(double)stats.total_read,
			(double)stats.total_size);
	} else if (am_server != 2) {
		const char *name;

		name = rerr_name(code);
		if (!name)
			name = "unexplained error";

		/* VANISHED is not an error, only a warning */
		if (code == RERR_VANISHED) {
			rprintf(FWARNING, "rsync warning: %s (code %d) at %s(%d) [%s=%s]\n",
				name, code, file, line, who_am_i(), RSYNC_VERSION);
		} else {
			rprintf(FERROR, "rsync error: %s (code %d) at %s(%d) [%s=%s]\n",
				name, code, file, line, who_am_i(), RSYNC_VERSION);
		}
	}
}