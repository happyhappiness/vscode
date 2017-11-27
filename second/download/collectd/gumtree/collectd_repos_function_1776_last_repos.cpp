void *dpdk_helper_priv_get(dpdk_helper_ctx_t *phc) {
  if (phc)
    return phc->priv_data;

  return NULL;
}