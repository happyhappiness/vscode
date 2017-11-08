void rflush(enum logcode code)
{
	FILE *f = NULL;

	if (am_daemon || code == FLOG)
		return;

	if (code == FINFO && !am_server)
		f = stdout;
	else
		f = stderr;

	fflush(f);
}