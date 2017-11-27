void c_complain (int level, c_complain_t *c, const char *format, ...)
{
	va_list ap;

	/* reset the old interval */
	if (c->interval < 0)
		c->interval *= -1;

	va_start (ap, format);
	vcomplain (level, c, format, ap);
	va_end (ap);
}