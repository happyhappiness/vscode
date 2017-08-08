{
	va_list ap;

	va_start(ap, fmt);
	archive_string_vsprintf(as, fmt, ap);
	va_end(ap);
}