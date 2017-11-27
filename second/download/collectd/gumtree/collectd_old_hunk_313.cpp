	if (list_notification == NULL)
		return (-1);

	le = llist_head (list_notification);
	while (le != NULL)
	{
		callback = (int (*) (const notification_t *)) le->value;
		(*callback) (notif);

		le = le->next;
	}

	return (0);
} /* int plugin_dispatch_notification */

void plugin_log (int level, const char *format, ...)
{
	char msg[1024];
	va_list ap;

	void (*callback) (int, const char *);
	llentry_t *le;

	if (list_log == NULL)
		return;

#if !COLLECT_DEBUG
