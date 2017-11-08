char *git_pathdup(const char *fmt, ...)
{
	char path[PATH_MAX], *ret;
	va_list args;
	va_start(args, fmt);
	ret = vsnpath(path, sizeof(path), fmt, args);
	va_end(args);
	return xstrdup(ret);
}