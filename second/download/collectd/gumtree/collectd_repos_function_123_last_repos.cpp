static int dpdk_stats_get_size(dpdk_helper_ctx_t *phc) {
  return dpdk_helper_data_size_get(phc) - sizeof(dpdk_stats_ctx_t);
}