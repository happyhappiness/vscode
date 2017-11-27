void plugin_complain (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;

	if (c->delay > 0)
	{
		c->delay--;
		return;
	}

	if (c->interval < interval_g)
		c->interval = interval_g;
	else
		c->interval *= 2;

	if (c->interval > 86400)
		c->interval = 86400;

	c->delay = c->interval / interval_g;

	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	plugin_log (level, message);
}