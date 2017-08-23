void
archive_set_error(struct archive *a, int error_number, const char *fmt, ...)
{
	va_list ap;

	a->archive_error_number = error_number;
	if (fmt == NULL) {
		a->error = NULL;
		return;
	}

	archive_string_empty(&(a->error_string));
	va_start(ap, fmt);
	archive_string_vsprintf(&(a->error_string), fmt, ap);
	va_end(ap);
	a->error = a->error_string.s;
}