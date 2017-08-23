void
archive_string_sprintf(struct archive_string *as, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	archive_string_vsprintf(as, fmt, ap);
	va_end(ap);
}