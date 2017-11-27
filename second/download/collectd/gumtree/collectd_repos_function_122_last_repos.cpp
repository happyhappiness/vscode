static int dpdk_helper_stats_count_get(dpdk_helper_ctx_t *phc) {
  uint8_t ports = dpdk_helper_eth_dev_count();
  if (ports == 0)
    return -ENODEV;

  dpdk_stats_ctx_t *ctx = DPDK_STATS_CTX_GET(phc);
  ctx->ports_count = ports;

  int len = 0;
  int stats_count = 0;
  for (int i = 0; i < ports; i++) {
    if (!(ctx->config.enabled_port_mask & (1 << i)))
      continue;
#if RTE_VERSION >= RTE_VERSION_16_07
    len = rte_eth_xstats_get_names(i, NULL, 0);
#else
    len = rte_eth_xstats_get(i, NULL, 0);
#endif
    if (len < 0) {
      DPDK_CHILD_LOG("%s: Cannot get stats count\n", DPDK_STATS_PLUGIN);
      return -1;
    }
    ctx->port_stats_count[i] = len;
    stats_count += len;
  }

  DPDK_CHILD_LOG("%s:%s:%d stats_count=%d\n", DPDK_STATS_PLUGIN, __FUNCTION__,
                 __LINE__, stats_count);

  return stats_count;
}