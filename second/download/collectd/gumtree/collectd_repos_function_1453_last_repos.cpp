static int ovs_events_plugin_config(oconfig_item_t *ci) {
  _Bool dispatch_values = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("SendNotification", child->key) == 0) {
      if (cf_util_get_boolean(child,
                              &ovs_events_ctx.config.send_notification) != 0) {
        ovs_events_config_free();
        return -1;
      }
    } else if (strcasecmp("Address", child->key) == 0) {
      if (cf_util_get_string_buffer(
              child, ovs_events_ctx.config.ovs_db_node,
              sizeof(ovs_events_ctx.config.ovs_db_node)) != 0) {
        ovs_events_config_free();
        return -1;
      }
    } else if (strcasecmp("Port", child->key) == 0) {
      char *service = NULL;
      if (cf_util_get_service(child, &service) != 0) {
        ovs_events_config_free();
        return -1;
      }
      sstrncpy(ovs_events_ctx.config.ovs_db_serv, service,
               sizeof(ovs_events_ctx.config.ovs_db_serv));
      sfree(service);
    } else if (strcasecmp("Socket", child->key) == 0) {
      if (cf_util_get_string_buffer(
              child, ovs_events_ctx.config.ovs_db_unix,
              sizeof(ovs_events_ctx.config.ovs_db_unix)) != 0) {
        ovs_events_config_free();
        return -1;
      }
    } else if (strcasecmp("Interfaces", child->key) == 0) {
      if (ovs_events_config_get_interfaces(child) != 0) {
        ovs_events_config_free();
        return -1;
      }
    } else if (strcasecmp("DispatchValues", child->key) == 0) {
      if (cf_util_get_boolean(child, &dispatch_values) != 0) {
        ovs_events_config_free();
        return -1;
      }
    } else {
      ERROR(OVS_EVENTS_PLUGIN ": option '%s' is not allowed here", child->key);
      ovs_events_config_free();
      return -1;
    }
  }
  /* Check and warn about invalid configuration */
  if (!ovs_events_ctx.config.send_notification && !dispatch_values) {
    WARNING(OVS_EVENTS_PLUGIN
            ": send notification and dispatch values "
            "options are disabled. No information will be dispatched by the "
            "plugin. Please check your configuration");
  }
  /* Dispatch link status values if configured */
  if (dispatch_values)
    return plugin_register_complex_read(NULL, OVS_EVENTS_PLUGIN,
                                        ovs_events_plugin_read, 0, NULL);

  return 0;
}