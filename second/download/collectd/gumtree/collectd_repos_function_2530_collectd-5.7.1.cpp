int notification_init(notification_t *n, int severity, const char *message,
                      const char *host, const char *plugin,
                      const char *plugin_instance, const char *type,
                      const char *type_instance) {
  memset(n, '\0', sizeof(notification_t));

  n->severity = severity;

  if (message != NULL)
    sstrncpy(n->message, message, sizeof(n->message));
  if (host != NULL)
    sstrncpy(n->host, host, sizeof(n->host));
  if (plugin != NULL)
    sstrncpy(n->plugin, plugin, sizeof(n->plugin));
  if (plugin_instance != NULL)
    sstrncpy(n->plugin_instance, plugin_instance, sizeof(n->plugin_instance));
  if (type != NULL)
    sstrncpy(n->type, type, sizeof(n->type));
  if (type_instance != NULL)
    sstrncpy(n->type_instance, type_instance, sizeof(n->type_instance));

  return (0);
}