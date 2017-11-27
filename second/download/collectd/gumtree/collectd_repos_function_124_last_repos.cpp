int dpdk_helper_command_handler(dpdk_helper_ctx_t *phc, enum DPDK_CMD cmd) {
  /* this function is called from helper context */

  if (phc == NULL) {
    DPDK_CHILD_LOG("%s: Invalid argument(phc)\n", DPDK_STATS_PLUGIN);
    return -EINVAL;
  }

  if (cmd != DPDK_CMD_GET_STATS) {
    DPDK_CHILD_LOG("%s: Unknown command (cmd=%d)\n", DPDK_STATS_PLUGIN, cmd);
    return -EINVAL;
  }

  int stats_count = dpdk_helper_stats_count_get(phc);
  if (stats_count < 0) {
    return stats_count;
  }

  DPDK_STATS_CTX_GET(phc)->stats_count = stats_count;
  int stats_size = stats_count * DPDK_STATS_CTX_GET_XSTAT_SIZE;

  if (dpdk_stats_get_size(phc) < stats_size) {
    DPDK_CHILD_LOG(
        DPDK_STATS_PLUGIN
        ":%s:%d not enough space for stats (available=%d, needed=%d)\n",
        __FUNCTION__, __LINE__, (int)dpdk_stats_get_size(phc), stats_size);
    return -ENOBUFS;
  }

  return dpdk_helper_stats_get(phc);
}