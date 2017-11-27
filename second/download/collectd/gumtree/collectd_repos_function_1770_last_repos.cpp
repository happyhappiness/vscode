static void dpdk_helper_config_default(dpdk_helper_ctx_t *phc) {
  if (phc == NULL)
    return;

  DPDK_HELPER_TRACE(phc->shm_name);

  snprintf(phc->eal_config.coremask, DATA_MAX_NAME_LEN, "%s", "0xf");
  snprintf(phc->eal_config.memory_channels, DATA_MAX_NAME_LEN, "%s", "1");
  snprintf(phc->eal_config.file_prefix, DATA_MAX_NAME_LEN, "%s",
           DPDK_DEFAULT_RTE_CONFIG);
}