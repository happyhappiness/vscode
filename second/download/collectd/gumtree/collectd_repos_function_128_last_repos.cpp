static int dpdk_stats_reinit_helper() {
  DPDK_STATS_TRACE();

  dpdk_stats_ctx_t *ctx = DPDK_STATS_CTX_GET(g_hc);

  size_t data_size = sizeof(dpdk_stats_ctx_t) +
                     (ctx->stats_count * DPDK_STATS_CTX_GET_XSTAT_SIZE);

  DEBUG("%s:%d helper reinit (new_size=%zu)", __FUNCTION__, __LINE__,
        data_size);

  dpdk_stats_ctx_t tmp_ctx;
  dpdk_eal_config_t tmp_eal;

  memcpy(&tmp_ctx, ctx, sizeof(dpdk_stats_ctx_t));
  dpdk_helper_eal_config_get(g_hc, &tmp_eal);

  dpdk_helper_shutdown(g_hc);

  g_hc = NULL;

  int ret;
  ret = dpdk_helper_init(g_shm_name, data_size, &g_hc);
  if (ret != 0) {
    char errbuf[ERR_BUF_SIZE];
    ERROR("%s: failed to initialize %s helper(error: %s)", DPDK_STATS_PLUGIN,
          g_shm_name, sstrerror(errno, errbuf, sizeof(errbuf)));
    return ret;
  }

  ctx = DPDK_STATS_CTX_GET(g_hc);
  memcpy(ctx, &tmp_ctx, sizeof(dpdk_stats_ctx_t));
  DPDK_STATS_CTX_INIT(ctx);
  dpdk_helper_eal_config_set(g_hc, &tmp_eal);

  return ret;
}