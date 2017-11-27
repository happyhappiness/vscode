int plugin_dispatch_notification (const notification_t *notif)
{
	llentry_t *le;
	/* Possible TODO: Add flap detection here */

	DEBUG ("plugin_dispatch_notification: severity = %i; message = %s; "
			"time = %u; host = %s;",
			notif->severity, notif->message,
			(unsigned int) notif->time, notif->host);

	/* Nobody cares for notifications */
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
}