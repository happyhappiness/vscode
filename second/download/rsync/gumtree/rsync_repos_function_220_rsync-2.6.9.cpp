void rflush(enum logcode code)
{
	FILE *f = NULL;

	if (am_daemon || code == FLOG)
		return;

	if (code == FERROR || am_server)
		f = stderr;
	else
		f = stdout;

	fflush(f);
}