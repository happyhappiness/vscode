void dpdk_helper_shutdown(dpdk_helper_ctx_t *phc) {
  if (phc == NULL)
    return;

  DPDK_HELPER_TRACE(phc->shm_name);

  close(phc->pipes[1]);

  if (phc->status != DPDK_HELPER_NOT_INITIALIZED) {
    dpdk_helper_exit_command(phc, DPDK_HELPER_GRACEFUL_QUIT);
  }

  sem_destroy(&phc->sema_cmd_start);
  sem_destroy(&phc->sema_cmd_complete);
  dpdk_shm_cleanup(phc->shm_name, phc->shm_size, (void *)phc);
}