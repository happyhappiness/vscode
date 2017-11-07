int winansi_fputs(const char *str, FILE *stream)
{
	int rv;

	if (!isatty(fileno(stream)))
		return fputs(str, stream);

	init();

	if (!console)
		return fputs(str, stream);

	rv = ansi_emulate(str, stream);

	if (rv >= 0)
		return 0;
	else
		return EOF;
}