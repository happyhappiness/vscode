static int dpdk_events_config(oconfig_item_t *ci) {
  DPDK_EVENTS_TRACE();
  int ret = dpdk_events_preinit();
  if (ret) {
    g_state |= DPDK_EVENTS_STATE_CFG_ERR;
    return 0;
  }

  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(g_hc);

  /* Disabling link_status and keep_alive since <Plugin/> config section
   * specifies if those should be enabled */
  ec->config.keep_alive.enabled = ec->config.link_status.enabled = 0;
  memset(&ec->config.keep_alive.lcore_mask, 0,
         sizeof(ec->config.keep_alive.lcore_mask));

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("EAL", child->key) == 0)
      ret = dpdk_helper_eal_config_parse(g_hc, child);
    else if (strcasecmp("Event", child->key) == 0) {
      char event_type[DATA_MAX_NAME_LEN];

      if (cf_util_get_string_buffer(child, event_type, sizeof(event_type)))
        ret = -1;
      else if (strcasecmp(event_type, "link_status") == 0) {
        ret = dpdk_events_link_status_config(ec, child);
        if (ret) {
          g_state |= DPDK_EVENTS_STATE_LS_CFG_ERR;
          continue;
        }
      } else if (strcasecmp(event_type, "keep_alive") == 0) {
        ret = dpdk_events_keep_alive_config(ec, child);
        if (ret) {
          g_state |= DPDK_EVENTS_STATE_KA_CFG_ERR;
          continue;
        }
      } else {
        ERROR(DPDK_EVENTS_PLUGIN ": The selected event \"%s\" is unknown.",
              event_type);
        ret = -1;
      }
    } else {
      ERROR(DPDK_EVENTS_PLUGIN ": unrecognized configuration option %s.",
            child->key);
      ret = -1;
    }

    if (ret != 0) {
      g_state |= DPDK_EVENTS_STATE_CFG_ERR;
      return 0;
    }
  }

  if (g_state & DPDK_EVENTS_STATE_KA_CFG_ERR) {
    ERROR(DPDK_EVENTS_PLUGIN
          ": Invalid keep alive configuration. Event disabled.");
    ec->config.keep_alive.enabled = 0;
  }

  if (g_state & DPDK_EVENTS_STATE_LS_CFG_ERR) {
    ERROR(DPDK_EVENTS_PLUGIN
          ": Invalid link status configuration. Event disabled.");
    ec->config.link_status.enabled = 0;
  }

  if (!ec->config.keep_alive.enabled && !ec->config.link_status.enabled) {
    ERROR(DPDK_EVENTS_PLUGIN ": At least one type of events should be "
                             "configured for collecting. Plugin misconfigured");
    g_state |= DPDK_EVENTS_STATE_CFG_ERR;
    return 0;
  }

  return 0;
}