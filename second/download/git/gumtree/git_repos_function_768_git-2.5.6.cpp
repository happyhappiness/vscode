static void status_printf_more(struct wt_status *s, const char *color,
			       const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	status_vprintf(s, 0, color, fmt, ap, NULL);
	va_end(ap);
}