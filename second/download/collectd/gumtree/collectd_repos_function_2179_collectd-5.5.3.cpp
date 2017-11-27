void c_do_release (int level, c_complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;

	if (c->interval == 0)
		return;

	c->interval = 0;
	c->complained_once = 0;

	va_start (ap, format);
	vsnprintf (message, sizeof (message), format, ap);
	message[sizeof (message) - 1] = '\0';
	va_end (ap);

	plugin_log (level, "%s", message);
}