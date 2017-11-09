void rflush(enum logcode code)
{
	FILE *f;

	if (am_daemon || code == FLOG)
		return;

	if (!am_server && (code == FINFO || code == FCLIENT))
		f = stdout;
	else
		f = stderr;

	fflush(f);
}