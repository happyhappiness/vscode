static void submit_notif(const virDomainPtr domain, int severity,
                         const char *msg, const char *type,
                         const char *type_instance) {
  notification_t notif;

  init_notif(&notif, domain, severity, msg, type, type_instance);
  plugin_dispatch_notification(&notif);
  if (notif.meta)
    plugin_notification_meta_free(notif.meta);
}