void status_printf(struct wt_status *s, const char *color,
			const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	status_vprintf(s, 1, color, fmt, ap, NULL);
	va_end(ap);
}