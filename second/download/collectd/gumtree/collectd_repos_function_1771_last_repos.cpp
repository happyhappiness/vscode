int dpdk_helper_eal_config_set(dpdk_helper_ctx_t *phc, dpdk_eal_config_t *ec) {
  if (phc == NULL) {
    ERROR("Invalid argument (phc)");
    return -EINVAL;
  }

  DPDK_HELPER_TRACE(phc->shm_name);

  if (ec == NULL) {
    ERROR("Invalid argument (ec)");
    return -EINVAL;
  }

  memcpy(&phc->eal_config, ec, sizeof(phc->eal_config));

  return 0;
}