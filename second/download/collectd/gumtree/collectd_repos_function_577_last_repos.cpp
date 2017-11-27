static int dpdk_events_link_status_config(dpdk_events_ctx_t *ec,
                                          oconfig_item_t *ci) {
  ec->config.link_status.enabled = 1;

  DEBUG(DPDK_EVENTS_PLUGIN ": Subscribed for Link Status Events.");

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("EnabledPortMask", child->key) == 0) {
      if (cf_util_get_int(child,
                          (int *)&ec->config.link_status.enabled_port_mask))
        return -1;
      DEBUG(DPDK_EVENTS_PLUGIN ": LinkStatus:Enabled Port Mask 0x%X",
            ec->config.link_status.enabled_port_mask);
    } else if (strcasecmp("SendEventsOnUpdate", child->key) == 0) {
      if (cf_util_get_boolean(child, &ec->config.link_status.send_updated))
        return -1;
      DEBUG(DPDK_EVENTS_PLUGIN ": LinkStatus:SendEventsOnUpdate %d",
            ec->config.link_status.send_updated);
    } else if (strcasecmp("SendNotification", child->key) == 0) {
      if (cf_util_get_boolean(child, &ec->config.link_status.notify))
        return -1;

      DEBUG(DPDK_EVENTS_PLUGIN ": LinkStatus:SendNotification %d",
            ec->config.link_status.notify);
    } else if (strcasecmp("PortName", child->key) != 0) {
      ERROR(DPDK_EVENTS_PLUGIN ": unrecognized configuration option %s.",
            child->key);
      return -1;
    }
  }

  int port_num = 0;

  /* parse port names after EnabledPortMask was parsed */
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("PortName", child->key) == 0) {
      while (!(ec->config.link_status.enabled_port_mask & (1 << port_num)))
        port_num++;

      if (cf_util_get_string_buffer(
              child, ec->config.link_status.port_name[port_num],
              sizeof(ec->config.link_status.port_name[port_num]))) {
        return -1;
      }
      DEBUG(DPDK_EVENTS_PLUGIN ": LinkStatus:Port %d Name: %s", port_num,
            ec->config.link_status.port_name[port_num]);
      port_num++;
    }
  }

  return 0;
}