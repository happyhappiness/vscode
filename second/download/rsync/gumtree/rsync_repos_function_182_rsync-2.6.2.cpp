void rwrite(enum logcode code, char *buf, int len)
{
	FILE *f=NULL;
	/* recursion can happen with certain fatal conditions */

	if (quiet && code == FINFO)
		return;

	if (len < 0)
		exit_cleanup(RERR_MESSAGEIO);

	buf[len] = 0;

	if (code == FLOG) {
		if (am_daemon) logit(LOG_INFO, buf);
		return;
	}

	if (am_server) {
		/* Pass it to non-server side, perhaps through our sibling. */
		if (msg_fd_out >= 0) {
			send_msg((enum msgcode)code, buf, len);
			return;
		}
		if (!am_daemon
		    && io_multiplex_write((enum msgcode)code, buf, len))
			return;
	}

	/* otherwise, if in daemon mode and either we are not a server
	 *  (that is, we are not running --daemon over a remote shell) or
	 *  the log has already been initialised, log the message on this
	 *  side because we don't want the client to see most errors for
	 *  security reasons.  We do want early messages when running daemon
	 *  mode over a remote shell to go to the remote side; those will
	 *  fall through to the next case.
	 * Note that this is only for the time before multiplexing is enabled.
	 */
	if (am_daemon && (!am_server || log_initialised)) {
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