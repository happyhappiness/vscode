int svndump_init(const char *filename)
{
	if (buffer_init(&input, filename))
		return error("cannot open %s: %s", filename ? filename : "NULL", strerror(errno));
	init(REPORT_FILENO);
	return 0;
}