int asprintf(char **ptr, const char *format, ...)
{
	va_list ap;
	int ret;
	
	va_start(ap, format);
	ret = vasprintf(ptr, format, ap);
	va_end(ap);

	return ret;
}