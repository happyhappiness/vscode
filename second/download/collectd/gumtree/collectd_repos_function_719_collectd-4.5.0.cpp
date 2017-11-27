static int c_notify (const notification_t *n)
{
	NotifyNotification *notification = NULL;
	NotifyUrgency       urgency      = NOTIFY_URGENCY_LOW;
	int                 timeout      = okay_timeout;

	char summary[1024];

	if (NOTIF_WARNING == n->severity) {
		urgency = NOTIFY_URGENCY_NORMAL;
		timeout = warn_timeout;
	}
	else if (NOTIF_FAILURE == n->severity) {
		urgency = NOTIFY_URGENCY_CRITICAL;
		timeout = fail_timeout;
	}

	ssnprintf (summary, sizeof (summary), "collectd %s notification",
			(NOTIF_FAILURE == n->severity) ? "FAILURE"
				: (NOTIF_WARNING == n->severity) ? "WARNING"
				: (NOTIF_OKAY == n->severity) ? "OKAY" : "UNKNOWN");

	notification = notify_notification_new (summary, n->message, NULL, NULL);
	if (NULL == notification) {
		log_err ("Failed to create a new notification.");
		return -1;
	}

	notify_notification_set_urgency (notification, urgency);
	notify_notification_set_timeout (notification, timeout);

	if (! notify_notification_show (notification, NULL))
		log_err ("Failed to display notification.");

	g_object_unref (G_OBJECT (notification));
	return 0;
}