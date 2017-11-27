static int init_notif(notification_t *notif, const virDomainPtr domain,
                      int severity, const char *msg, const char *type,
                      const char *type_instance) {
  value_list_t vl = VALUE_LIST_INIT;

  if (!notif) {
    ERROR(PLUGIN_NAME ": init_notif: NULL pointer");
    return -1;
  }

  init_value_list(&vl, domain);
  notification_init(notif, severity, msg, vl.host, vl.plugin,
                    vl.plugin_instance, type, type_instance);
  notif->time = cdtime();
  return 0;
}