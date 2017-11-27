static int dpdk_stats_counters_dispatch(dpdk_helper_ctx_t *phc) {
  dpdk_stats_ctx_t *ctx = DPDK_STATS_CTX_GET(phc);

  /* dispatch stats values to collectd */

  DEBUG("%s:%s:%d ports=%u", DPDK_STATS_PLUGIN, __FUNCTION__, __LINE__,
        ctx->ports_count);

  int stats_count = 0;

  for (int i = 0; i < ctx->ports_count; i++) {
    if (!(ctx->config.enabled_port_mask & (1 << i)))
      continue;

    char dev_name[64];
    if (ctx->config.port_name[i][0] != 0) {
      snprintf(dev_name, sizeof(dev_name), "%s", ctx->config.port_name[i]);
    } else {
      snprintf(dev_name, sizeof(dev_name), "port.%d", i);
    }

    DEBUG(" === Dispatch stats for port %d (name=%s; stats_count=%d)", i,
          dev_name, ctx->port_stats_count[i]);

    for (int j = 0; j < ctx->port_stats_count[i]; j++) {
      const char *cnt_name = DPDK_STATS_XSTAT_GET_NAME(ctx, stats_count);
      if (cnt_name == NULL)
        WARNING("dpdkstat: Invalid counter name");
      else
        dpdk_stats_counter_submit(
            dev_name, cnt_name,
            (derive_t)DPDK_STATS_XSTAT_GET_VALUE(ctx, stats_count),
            ctx->port_read_time[i]);
      stats_count++;

      assert(stats_count <= ctx->stats_count);
    }
  }

  return 0;
}