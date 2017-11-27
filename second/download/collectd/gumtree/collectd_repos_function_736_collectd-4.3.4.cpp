int plugin_unregister_notification (const char *name)
{
	return (plugin_unregister (list_notification, name));
}