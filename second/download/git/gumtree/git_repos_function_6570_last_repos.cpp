int svndump_init(const char *filename)
{
	if (buffer_init(&input, filename))
		return error_errno("cannot open %s", filename ? filename : "NULL");
	init(REPORT_FILENO);
	return 0;
}