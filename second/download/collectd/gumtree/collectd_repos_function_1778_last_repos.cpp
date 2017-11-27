int dpdk_helper_init(const char *name, size_t data_size,
                     dpdk_helper_ctx_t **pphc) {
  dpdk_helper_ctx_t *phc = NULL;
  size_t shm_size = sizeof(dpdk_helper_ctx_t) + data_size;
  char errbuf[ERR_BUF_SIZE];

  if (pphc == NULL) {
    ERROR("%s:Invalid argument(pphc)", __FUNCTION__);
    return -EINVAL;
  }

  if (name == NULL) {
    ERROR("%s:Invalid argument(name)", __FUNCTION__);
    return -EINVAL;
  }

  DPDK_HELPER_TRACE(name);

  /* Allocate dpdk_helper_ctx_t and
  * initialize a POSIX SHared Memory (SHM) object.
  */
  int err = dpdk_shm_init(name, shm_size, (void **)&phc);
  if (err != 0) {
    return -errno;
  }

  err = sem_init(&phc->sema_cmd_start, 1, 0);
  if (err != 0) {
    ERROR("sema_cmd_start semaphore init failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    int errno_m = errno;
    dpdk_shm_cleanup(name, shm_size, (void *)phc);
    return -errno_m;
  }

  err = sem_init(&phc->sema_cmd_complete, 1, 0);
  if (err != 0) {
    ERROR("sema_cmd_complete semaphore init failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    sem_destroy(&phc->sema_cmd_start);
    int errno_m = errno;
    dpdk_shm_cleanup(name, shm_size, (void *)phc);
    return -errno_m;
  }

  phc->shm_size = shm_size;
  sstrncpy(phc->shm_name, name, sizeof(phc->shm_name));

  dpdk_helper_config_default(phc);

  *pphc = phc;

  return 0;
}