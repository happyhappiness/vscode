	if (list_notification == NULL)
		return (-1);

	le = llist_head (list_notification);
	while (le != NULL)
	{
		callback_func_t *cf;
		plugin_notification_cb callback;
		int status;

		cf = le->value;
		callback = cf->cf_callback;
		status = (*callback) (notif, &cf->cf_udata);
		if (status != 0)
		{
			WARNING ("plugin_dispatch_notification: Notification "
					"callback %s returned %i.",
					le->key, status);
		}

		le = le->next;
	}

	return (0);
} /* int plugin_dispatch_notification */

void plugin_log (int level, const char *format, ...)
{
	char msg[1024];
	va_list ap;
	llentry_t *le;

	if (list_log == NULL)
		return;

#if !COLLECT_DEBUG
