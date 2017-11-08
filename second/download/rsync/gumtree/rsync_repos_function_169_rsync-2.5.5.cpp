void rwrite(enum logcode code, char *buf, int len)
{
	FILE *f=NULL;
	extern int am_daemon;
	extern int am_server;
	extern int quiet;
	/* recursion can happen with certain fatal conditions */

	if (quiet && code == FINFO) return;

	if (len < 0) exit_cleanup(RERR_MESSAGEIO);

	buf[len] = 0;

	if (code == FLOG) {
		if (am_daemon) logit(LOG_INFO, buf);
		return;
	}

	/* first try to pass it off to our sibling */
	if (am_server && log_error_fd != -1) {
		err_list_add(code, buf, len);
		err_list_push();
		return;
	}

	/* If that fails, try to pass it to the other end.
	 *
	 * io_multiplex_write can fail if we do not have a multiplexed
	 * connection at the moment, in which case we fall through and
	 * log locally instead. */
	if (am_server && io_multiplex_write(code, buf, len)) {
		return;
	}

	if (am_daemon) {
		static int depth;
		int priority = LOG_INFO;
		if (code == FERROR) priority = LOG_WARNING;

		if (depth) return;

		depth++;

		log_init();
		logit(priority, buf);

		depth--;
		return;
	}

	if (code == FERROR) {
		log_got_error = 1;
		f = stderr;
	} 

	if (code == FINFO) {
		if (am_server) 
			f = stderr;
		else
			f = stdout;
	} 

	if (!f) exit_cleanup(RERR_MESSAGEIO);

	if (fwrite(buf, len, 1, f) != 1) exit_cleanup(RERR_MESSAGEIO);

	if (buf[len-1] == '\r' || buf[len-1] == '\n') fflush(f);
}