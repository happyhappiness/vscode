int dpdk_helper_eal_config_get(dpdk_helper_ctx_t *phc, dpdk_eal_config_t *ec) {
  if (phc == NULL) {
    ERROR("Invalid argument (phc)");
    return -EINVAL;
  }

  DPDK_HELPER_TRACE(phc->shm_name);

  if (ec == NULL) {
    ERROR("Invalid argument (ec)");
    return -EINVAL;
  }

  memcpy(ec, &phc->eal_config, sizeof(*ec));

  return 0;
}