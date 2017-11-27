int plugin_register_notification (const char *name,
		int (*callback) (const notification_t *notif))
{
	return (register_callback (&list_notification, name, (void *) callback));
}