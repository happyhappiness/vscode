void plugin_log (int level, const char *format, ...)
{
	char msg[1024];
	va_list ap;
	llentry_t *le;

	if (list_log == NULL)
		return;

#if !COLLECT_DEBUG
	if (level >= LOG_DEBUG)
		return;
#endif

	va_start (ap, format);
	vsnprintf (msg, sizeof (msg), format, ap);
	msg[sizeof (msg) - 1] = '\0';
	va_end (ap);

	le = llist_head (list_log);
	while (le != NULL)
	{
		callback_func_t *cf;
		plugin_log_cb callback;

		cf = le->value;
		callback = cf->cf_callback;

		(*callback) (level, msg, &cf->cf_udata);

		le = le->next;
	}
}