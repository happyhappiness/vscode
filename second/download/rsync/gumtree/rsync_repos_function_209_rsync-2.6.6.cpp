void rwrite(enum logcode code, char *buf, int len)
{
	FILE *f = NULL;
	/* recursion can happen with certain fatal conditions */

	if (quiet && code == FINFO)
		return;

	if (len < 0)
		exit_cleanup(RERR_MESSAGEIO);

	buf[len] = 0;

	if (am_server && msg_fd_out >= 0) {
		/* Pass the message to our sibling. */
		send_msg((enum msgcode)code, buf, len);
		return;
	}

	if (code == FCLIENT)
		code = FINFO;
	else if (am_daemon) {
		static int in_block;
		char msg[2048];
		int priority = code == FERROR ? LOG_WARNING : LOG_INFO;

		if (in_block)
			return;
		in_block = 1;
		if (!log_initialised)
			log_init();
		strlcpy(msg, buf, MIN((int)sizeof msg, len + 1));
		logit(priority, msg);
		in_block = 0;

		if (code == FLOG || !am_server)
			return;
	} else if (code == FLOG)
		return;

	if (am_server) {
		/* Pass the message to the non-server side. */
		if (io_multiplex_write((enum msgcode)code, buf, len))
			return;
		if (am_daemon) {
			/* TODO: can we send the error to the user somehow? */
			return;
		}
	}

	if (code == FERROR) {
		log_got_error = 1;
		f = stderr;
	}

	if (code == FINFO)
		f = am_server ? stderr : stdout;

	if (!f)
		exit_cleanup(RERR_MESSAGEIO);

	if (fwrite(buf, len, 1, f) != 1)
		exit_cleanup(RERR_MESSAGEIO);

	if (buf[len-1] == '\r' || buf[len-1] == '\n')
		fflush(f);
}