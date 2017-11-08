char *git_path(const char *fmt, ...)
{
	char *pathname = get_pathname();
	va_list args;
	char *ret;

	va_start(args, fmt);
	ret = vsnpath(pathname, PATH_MAX, fmt, args);
	va_end(args);
	return ret;
}