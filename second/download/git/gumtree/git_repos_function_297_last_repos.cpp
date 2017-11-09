void walker_say(struct walker *walker, const char *fmt, ...)
{
	if (walker->get_verbosely) {
		va_list ap;
		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
	}
}