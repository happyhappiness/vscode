int dpdk_helper_data_size_get(dpdk_helper_ctx_t *phc) {
  if (phc == NULL) {
    DPDK_CHILD_LOG("Invalid argument(phc)\n");
    return -EINVAL;
  }

  return phc->shm_size - sizeof(dpdk_helper_ctx_t);
}