static int dpdk_helper_stats_get(dpdk_helper_ctx_t *phc) {
  int len = 0;
  int ret = 0;
  int stats = 0;
  dpdk_stats_ctx_t *ctx = DPDK_STATS_CTX_GET(phc);

  /* get stats from DPDK */
  for (uint8_t i = 0; i < ctx->ports_count; i++) {
    if (!(ctx->config.enabled_port_mask & (1 << i)))
      continue;

    ctx->port_read_time[i] = cdtime();
    /* Store available stats array length for port */
    len = ctx->port_stats_count[i];

    ret = rte_eth_xstats_get(i, &ctx->xstats[stats], len);
    if (ret < 0 || ret > len) {
      DPDK_CHILD_LOG(DPDK_STATS_PLUGIN
                     ": Error reading stats (port=%d; len=%d, ret=%d)\n",
                     i, len, ret);
      ctx->port_stats_count[i] = 0;
      return -1;
    }
#if RTE_VERSION >= RTE_VERSION_16_07
    ret = rte_eth_xstats_get_names(i, &ctx->xnames[stats], len);
    if (ret < 0 || ret > len) {
      DPDK_CHILD_LOG(DPDK_STATS_PLUGIN
                     ": Error reading stat names (port=%d; len=%d ret=%d)\n",
                     i, len, ret);
      ctx->port_stats_count[i] = 0;
      return -1;
    }
#endif
    ctx->port_stats_count[i] = ret;
    stats += ctx->port_stats_count[i];
  }

  assert(stats <= ctx->stats_count);
  return 0;
}