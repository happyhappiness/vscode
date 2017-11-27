int plugin_dispatch_notification (const notification_t *notif)
{
	int (*callback) (const notification_t *);
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
		callback = (int (*) (const notification_t *)) le->value;
		(*callback) (notif);

		le = le->next;
	}

	return (0);
}