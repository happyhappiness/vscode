void log_exit(int code, const char *file, int line)
{
	if (code == 0) {
		rprintf(FLOG,"sent %s bytes  received %s bytes  total size %s\n",
			big_num(stats.total_written),
			big_num(stats.total_read),
			big_num(stats.total_size));
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