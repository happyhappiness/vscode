static void ovs_events_conn_terminate() {
  const char msg[] = "OVS DB connection has been lost";
  if (ovs_events_ctx.config.send_notification)
    ovs_events_dispatch_terminate_notification(msg);
  WARNING(OVS_EVENTS_PLUGIN ": %s", msg);
  OVS_EVENTS_CTX_LOCK { ovs_events_ctx.is_db_available = 0; }
}