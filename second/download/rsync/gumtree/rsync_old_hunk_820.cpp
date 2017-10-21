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


/* This is the rsync debugging function. Call it with FINFO, FERROR or
 * FLOG. */
void rprintf(enum logcode code, const char *format, ...)
{
	va_list ap;
	char buf[MAXPATHLEN+512];
	size_t len;

	va_start(ap, format);
	len = vsnprintf(buf, sizeof buf, format, ap);
	va_end(ap);

	/* Deal with buffer overruns.  Instead of panicking, just
	 * truncate the resulting string.  (Note that configure ensures
	 * that we have a vsnprintf() that doesn't ever return -1.) */
	if (len > sizeof buf - 1) {
		const char ellipsis[] = "[...]";

		/* Reset length, and zero-terminate the end of our buffer */
		len = sizeof buf - 1;
		buf[len] = '\0';

		/* Copy the ellipsis to the end of the string, but give
