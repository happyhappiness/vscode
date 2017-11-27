static int dpdk_stats_config(oconfig_item_t *ci) {
  DPDK_STATS_TRACE();

  int ret = dpdk_stats_preinit();
  if (ret) {
    g_state = DPDK_STAT_STATE_CFG_ERR;
    return 0;
  }

  dpdk_stats_ctx_t *ctx = DPDK_STATS_CTX_GET(g_hc);

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("EnabledPortMask", child->key) == 0)
      ret = cf_util_get_int(child, (int *)&ctx->config.enabled_port_mask);
    else if (strcasecmp("SharedMemObj", child->key) == 0) {
      ret = cf_util_get_string_buffer(child, g_shm_name, sizeof(g_shm_name));
      if (ret == 0)
        ret = dpdk_stats_reinit_helper();
    } else if (strcasecmp("EAL", child->key) == 0)
      ret = dpdk_helper_eal_config_parse(g_hc, child);
    else if (strcasecmp("PortName", child->key) != 0) {
      ERROR(DPDK_STATS_PLUGIN ": unrecognized configuration option %s",
            child->key);
      ret = -1;
    }

    if (ret != 0) {
      g_state = DPDK_STAT_STATE_CFG_ERR;
      return 0;
    }
  }

  DEBUG(DPDK_STATS_PLUGIN ": Enabled Port Mask 0x%X",
        ctx->config.enabled_port_mask);
  DEBUG(DPDK_STATS_PLUGIN ": Shared memory object %s", g_shm_name);

  int port_num = 0;

  /* parse port names after EnabledPortMask was parsed */
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("PortName", child->key) == 0) {

      while (!(ctx->config.enabled_port_mask & (1 << port_num)))
        port_num++;

      if (cf_util_get_string_buffer(child, ctx->config.port_name[port_num],
                                    sizeof(ctx->config.port_name[port_num]))) {
        g_state = DPDK_STAT_STATE_CFG_ERR;
        return 0;
      }

      DEBUG(DPDK_STATS_PLUGIN ": Port %d Name: %s", port_num,
            ctx->config.port_name[port_num]);

      port_num++;
    }
  }

  return 0;
}