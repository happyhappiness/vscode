static int vcomplain (int level, c_complain_t *c,
		const char *format, va_list ap)
{
	time_t now;
	char   message[512];

	now = time (NULL);

	if (c->last + c->interval > now)
		return 0;

	c->last = now;

	if (c->interval < interval_g)
		c->interval = interval_g;
	else
		c->interval *= 2;

	if (c->interval > 86400)
		c->interval = 86400;

	vsnprintf (message, sizeof (message), format, ap);
	message[sizeof (message) - 1] = '\0';

	plugin_log (level, "%s", message);
	return 1;
}