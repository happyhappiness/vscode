static int dpdk_events_keep_alive_config(dpdk_events_ctx_t *ec,
                                         oconfig_item_t *ci) {
  ec->config.keep_alive.enabled = 1;
  DEBUG(DPDK_EVENTS_PLUGIN ": Subscribed for Keep Alive Events.");

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("SendEventsOnUpdate", child->key) == 0) {
      if (cf_util_get_boolean(child, &ec->config.keep_alive.send_updated))
        return -1;

      DEBUG(DPDK_EVENTS_PLUGIN ": KeepAlive:SendEventsOnUpdate %d",
            ec->config.keep_alive.send_updated);
    } else if (strcasecmp("LCoreMask", child->key) == 0) {
      char lcore_mask[DATA_MAX_NAME_LEN];

      if (cf_util_get_string_buffer(child, lcore_mask, sizeof(lcore_mask)))
        return -1;
      ec->config.keep_alive.lcore_mask =
          str_to_uint128(lcore_mask, strlen(lcore_mask));
      DEBUG(DPDK_EVENTS_PLUGIN ": KeepAlive:LCoreMask 0x%" PRIX64 "%" PRIX64 "",
            ec->config.keep_alive.lcore_mask.high,
            ec->config.keep_alive.lcore_mask.low);
    } else if (strcasecmp("KeepAliveShmName", child->key) == 0) {
      if (cf_util_get_string_buffer(child, ec->config.keep_alive.shm_name,
                                    sizeof(ec->config.keep_alive.shm_name)))
        return -1;

      DEBUG(DPDK_EVENTS_PLUGIN ": KeepAlive:KeepAliveShmName %s",
            ec->config.keep_alive.shm_name);
    } else if (strcasecmp("SendNotification", child->key) == 0) {
      if (cf_util_get_boolean(child, &ec->config.keep_alive.notify))
        return -1;

      DEBUG(DPDK_EVENTS_PLUGIN ": KeepAlive:SendNotification %d",
            ec->config.keep_alive.notify);
    } else {
      ERROR(DPDK_EVENTS_PLUGIN ": unrecognized configuration option %s.",
            child->key);
      return -1;
    }
  }

  return 0;
}