int notification_init (notification_t *n, int severity, const char *message,
		const char *host,
		const char *plugin, const char *plugin_instance,
		const char *type, const char *type_instance)
{
	memset (n, '\0', sizeof (notification_t));

	n->severity = severity;

	if (message != NULL)
		strncpy (n->message, message, sizeof (n->message));
	if (host != NULL)
		strncpy (n->host, host, sizeof (n->host));
	if (plugin != NULL)
		strncpy (n->plugin, plugin, sizeof (n->plugin));
	if (plugin_instance != NULL)
		strncpy (n->plugin_instance, plugin_instance,
				sizeof (n->plugin_instance));
	if (type != NULL)
		strncpy (n->type, type, sizeof (n->type));
	if (type_instance != NULL)
		strncpy (n->type_instance, type_instance,
				sizeof (n->type_instance));

	n->message[sizeof (n->message) - 1] = '\0';
	n->host[sizeof (n->host) - 1] = '\0';
	n->plugin[sizeof (n->plugin) - 1] = '\0';
	n->plugin_instance[sizeof (n->plugin_instance) - 1] = '\0';
	n->type[sizeof (n->type) - 1] = '\0';
	n->type_instance[sizeof (n->type_instance) - 1] = '\0';

	return (0);
}