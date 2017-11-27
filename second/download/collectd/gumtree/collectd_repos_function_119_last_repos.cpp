static int dpdk_stats_preinit(void) {
  DPDK_STATS_TRACE();

  if (g_hc != NULL) {
    /* already initialized if config callback was called before init callback */
    DEBUG("dpdk_stats_preinit: helper already initialized");
    return 0;
  }

  int ret = dpdk_helper_init(g_shm_name, sizeof(dpdk_stats_ctx_t), &g_hc);
  if (ret != 0) {
    char errbuf[ERR_BUF_SIZE];
    ERROR("%s: failed to initialize %s helper(error: %s)", DPDK_STATS_PLUGIN,
          g_shm_name, sstrerror(errno, errbuf, sizeof(errbuf)));
    return ret;
  }

  dpdk_stats_default_config();
  return ret;
}