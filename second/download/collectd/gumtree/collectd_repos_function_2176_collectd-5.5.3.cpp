static int vcomplain (int level, c_complain_t *c,
		const char *format, va_list ap)
{
	cdtime_t now;
	char   message[512];

	now = cdtime ();

	if (c->last + c->interval > now)
		return 0;

	c->last = now;

	if (c->interval < plugin_get_interval ())
		c->interval = plugin_get_interval ();
	else
		c->interval *= 2;

	if (c->interval > TIME_T_TO_CDTIME_T (86400))
		c->interval = TIME_T_TO_CDTIME_T (86400);

	vsnprintf (message, sizeof (message), format, ap);
	message[sizeof (message) - 1] = '\0';

	plugin_log (level, "%s", message);
	return 1;
}