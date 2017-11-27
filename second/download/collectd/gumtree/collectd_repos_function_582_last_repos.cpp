static void dpdk_events_notification_dispatch(int severity,
                                              const char *plugin_instance,
                                              cdtime_t time, const char *msg) {
  notification_t n = {
      .severity = severity, .time = time, .plugin = DPDK_EVENTS_PLUGIN};
  sstrncpy(n.host, hostname_g, sizeof(n.host));
  sstrncpy(n.plugin_instance, plugin_instance, sizeof(n.plugin_instance));
  sstrncpy(n.message, msg, sizeof(n.message));
  plugin_dispatch_notification(&n);
}