static int dpdk_stats_init(void) {
  DPDK_STATS_TRACE();
  int ret = 0;

  if (g_state != DPDK_STAT_STATE_OKAY) {
    dpdk_stats_shutdown();
    return -1;
  }

  ret = dpdk_stats_preinit();
  if (ret != 0) {
    return ret;
  }

  return 0;
}