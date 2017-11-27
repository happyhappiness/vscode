static int ovs_events_plugin_shutdown(void) {
  /* destroy OVS DB */
  if (ovs_db_destroy(ovs_events_ctx.ovs_db))
    ERROR(OVS_EVENTS_PLUGIN ": OVSDB object destroy failed");

  /* release memory allocated for config */
  ovs_events_config_free();

  DEBUG(OVS_EVENTS_PLUGIN ": plugin has been destroyed");
  return 0;
}