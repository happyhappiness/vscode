int write_file(const char *path, const char *fmt, ...)
{
	int status;
	va_list params;

	va_start(params, fmt);
	status = write_file_v(path, 1, fmt, params);
	va_end(params);
	return status;
}