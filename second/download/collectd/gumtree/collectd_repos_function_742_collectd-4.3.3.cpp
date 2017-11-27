void plugin_log (int level, const char *format, ...)
{
	char msg[512];
	va_list ap;

	void (*callback) (int, const char *);
	llentry_t *le;

	if (list_log == NULL)
		return;

#if !COLLECT_DEBUG
	if (level >= LOG_DEBUG)
		return;
#endif

	va_start (ap, format);
	vsnprintf (msg, 512, format, ap);
	msg[511] = '\0';
	va_end (ap);

	le = llist_head (list_log);
	while (le != NULL)
	{
		callback = (void (*) (int, const char *)) le->value;
		(*callback) (level, msg);

		le = le->next;
	}
}