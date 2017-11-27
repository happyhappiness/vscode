static void ovs_events_dispatch_terminate_notification(const char *msg) {
  notification_t n = {
      NOTIF_FAILURE, cdtime(), "", "", OVS_EVENTS_PLUGIN, "", "", "", NULL};
  sstrncpy(n.message, msg, sizeof(n.message));
  sstrncpy(n.host, hostname_g, sizeof(n.host));
  plugin_dispatch_notification(&n);
}