static int dpdk_helper_cmd_wait(dpdk_helper_ctx_t *phc, pid_t ppid) {
  DPDK_CHILD_TRACE(phc->shm_name);

  struct timespec ts;
  cdtime_t now = cdtime();
  cdtime_t cmd_wait_time = MS_TO_CDTIME_T(1500) + phc->cmd_wait_time * 2;
  ts = CDTIME_T_TO_TIMESPEC(now + cmd_wait_time);

  int ret = sem_timedwait(&phc->sema_cmd_start, &ts);
  DPDK_CHILD_LOG("%s:%s:%d pid=%lu got sema_cmd_start (ret=%d, errno=%d)\n",
                 phc->shm_name, __FUNCTION__, __LINE__, (long)getpid(), ret,
                 errno);

  if (phc->cmd == DPDK_CMD_QUIT) {
    DPDK_CHILD_LOG("%s:%s:%d pid=%lu exiting\n", phc->shm_name, __FUNCTION__,
                   __LINE__, (long)getpid());
    exit(0);
  } else if (ret == -1 && errno == ETIMEDOUT) {
    if (phc->status == DPDK_HELPER_ALIVE_SENDING_EVENTS) {
      DPDK_CHILD_LOG("%s:dpdk_helper_cmd_wait: sem timedwait()"
                     " timeout, did collectd terminate?\n",
                     phc->shm_name);
      dpdk_helper_exit(phc, DPDK_HELPER_GRACEFUL_QUIT);
    }
  }
#if COLLECT_DEBUG
  int val = 0;
  if (sem_getvalue(&phc->sema_cmd_start, &val) == 0)
    DPDK_CHILD_LOG("%s:%s:%d pid=%lu wait sema_cmd_start (value=%d)\n",
                   phc->shm_name, __FUNCTION__, __LINE__, (long)getpid(), val);
#endif

  /* Parent PID change means collectd died so quit the helper process. */
  if (ppid != getppid()) {
    DPDK_CHILD_LOG("dpdk_helper_cmd_wait: parent PID changed, quitting.\n");
    dpdk_helper_exit(phc, DPDK_HELPER_GRACEFUL_QUIT);
  }

  /* Checking for DPDK primary process. */
  if (!rte_eal_primary_proc_alive(phc->eal_config.file_prefix)) {
    if (phc->eal_initialized) {
      DPDK_CHILD_LOG(
          "%s:dpdk_helper_cmd_wait: no primary alive but EAL initialized:"
          " quitting.\n",
          phc->shm_name);
      dpdk_helper_exit(phc, DPDK_HELPER_NOT_INITIALIZED);
    }

    phc->status = DPDK_HELPER_WAITING_ON_PRIMARY;
    DPDK_CHILD_LOG("%s:%s:%d DPDK_HELPER_WAITING_ON_PRIMARY\n", phc->shm_name,
                   __FUNCTION__, __LINE__);

    return -1;
  }

  if (!phc->eal_initialized) {
    int ret = dpdk_helper_eal_init(phc);
    if (ret != 0) {
      DPDK_CHILD_LOG("Error initializing EAL\n");
      dpdk_helper_exit(phc, DPDK_HELPER_NOT_INITIALIZED);
    }
    phc->status = DPDK_HELPER_ALIVE_SENDING_EVENTS;
    DPDK_CHILD_LOG("%s:%s:%d DPDK_HELPER_ALIVE_SENDING_EVENTS\n", phc->shm_name,
                   __FUNCTION__, __LINE__);
    return -1;
  }

  return 0;
}