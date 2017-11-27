static int dpdk_stats_read(user_data_t *ud) {
  DPDK_STATS_TRACE();

  int ret = 0;

  if (g_hc == NULL) {
    ERROR("dpdk stats plugin not initialized");
    return -EINVAL;
  }

  dpdk_stats_ctx_t *ctx = DPDK_STATS_CTX_GET(g_hc);

  int result = 0;
  ret = dpdk_helper_command(g_hc, DPDK_CMD_GET_STATS, &result,
                            ctx->config.interval);
  if (ret != 0) {
    return 0;
  }

  if (result == -ENOBUFS) {
    dpdk_stats_reinit_helper();
  } else if (result == -ENODEV) {
    dpdk_helper_shutdown(g_hc);
  } else if (result == 0) {
    dpdk_stats_counters_dispatch(g_hc);
  }

  return 0;
}