static void say(const struct am_state *state, FILE *fp, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (!state->quiet) {
		vfprintf(fp, fmt, ap);
		putc('\n', fp);
	}
	va_end(ap);
}