int git_snprintf(char *str, size_t maxsize, const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = git_vsnprintf(str, maxsize, format, ap);
	va_end(ap);

	return ret;
}