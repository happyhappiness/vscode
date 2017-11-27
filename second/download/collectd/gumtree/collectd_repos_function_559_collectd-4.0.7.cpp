void plugin_relief (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;

	if (c->interval == 0)
		return;

	c->interval = 0;

	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	plugin_log (level, message);
}