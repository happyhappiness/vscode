void rflush(enum logcode code)
{
	FILE *f = NULL;

	if (am_daemon) {
		return;
	}

	if (code == FLOG) {
		return;
	}

	if (code == FERROR) {
		f = stderr;
	}

	if (code == FINFO) {
		if (am_server)
			f = stderr;
		else
			f = stdout;
	}

	if (!f) exit_cleanup(RERR_MESSAGEIO);
	fflush(f);
}