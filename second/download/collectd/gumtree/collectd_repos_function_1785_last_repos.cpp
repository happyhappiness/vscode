static int dpdk_helper_worker(dpdk_helper_ctx_t *phc) {
  DPDK_CHILD_TRACE(phc->shm_name);

  pid_t ppid = getppid();

  while (1) {
    if (dpdk_helper_cmd_wait(phc, ppid) == 0) {
      DPDK_CHILD_LOG("%s:%s:%d DPDK command handle (cmd=%d, pid=%lu)\n",
                     phc->shm_name, __FUNCTION__, __LINE__, phc->cmd,
                     (long)getpid());
      phc->cmd_result = dpdk_helper_command_handler(phc, phc->cmd);
    } else {
      phc->cmd_result = -1;
    }

    /* now kick collectd to get results */
    int err = sem_post(&phc->sema_cmd_complete);
    DPDK_CHILD_LOG("%s:%s:%d post sema_cmd_complete (pid=%lu)\n", phc->shm_name,
                   __FUNCTION__, __LINE__, (long)getpid());
    if (err) {
      char errbuf[ERR_BUF_SIZE];
      DPDK_CHILD_LOG("dpdk_helper_worker: error posting sema_cmd_complete "
                     "semaphore (%s)\n",
                     sstrerror(errno, errbuf, sizeof(errbuf)));
    }

#if COLLECT_DEBUG
    int val = 0;
    if (sem_getvalue(&phc->sema_cmd_complete, &val) == 0)
      DPDK_CHILD_LOG("%s:%s:%d pid=%lu sema_cmd_complete (value=%d)\n",
                     phc->shm_name, __FUNCTION__, __LINE__, (long)getpid(),
                     val);
#endif

  } /* while(1) */

  return 0;
}