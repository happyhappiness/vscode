int rsync_vsnprintf (char *str, size_t count, const char *fmt, va_list args)
{
	return dopr(str, count, fmt, args);
}