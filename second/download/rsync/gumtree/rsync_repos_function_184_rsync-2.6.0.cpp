void rflush(enum logcode code)
{
	FILE *f = NULL;
	extern int am_daemon;
	
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
		extern int am_server;
		if (am_server)
			f = stderr;
		else
			f = stdout;
	}

	if (!f) exit_cleanup(RERR_MESSAGEIO);
	fflush(f);
}