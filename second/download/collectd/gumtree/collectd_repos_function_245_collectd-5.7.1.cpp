static int dpdk_read(user_data_t *ud) {
  int ret = 0;

  /*
   * Check if SHM flag is set to be re-initialized. AKA DPDK ports have been
   * counted, so re-init SHM to be large enough to fit all the statistics.
   */
  if (g_configuration->collectd_reinit_shm) {
    DEBUG("dpdkstat: read() now reinit SHM then launching send-thread");
    dpdk_re_init_shm();
  }

  /*
   * Check if DPDK proc is alive, and has already counted port / stats. This
   * must be done in dpdk_read(), because the DPDK primary process may not be
   * alive at dpdk_init() time.
   */
  if (g_configuration->helper_status == DPDK_HELPER_NOT_INITIALIZED ||
      g_configuration->helper_status == DPDK_HELPER_GRACEFUL_QUIT) {
    int action = DPDK_HELPER_ACTION_SEND_STATS;
    if (g_configuration->num_xstats == 0)
      action = DPDK_HELPER_ACTION_COUNT_STATS;
    /* Spawn the helper thread to count stats or to read stats. */
    int err = dpdk_helper_spawn(action);
    if (err) {
      char errbuf[ERR_BUF_SIZE];
      ERROR("dpdkstat: error spawning helper %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return -1;
    }
  }

  pid_t ws = waitpid(g_configuration->helper_pid, NULL, WNOHANG);
  /*
   * Conditions under which to respawn helper:
   *  waitpid() fails, helper process died (or quit), so respawn
   */
  _Bool respawn_helper = 0;
  if (ws != 0) {
    respawn_helper = 1;
  }

  char buf[DPDKSTAT_MAX_BUFFER_SIZE];
  char out[DPDKSTAT_MAX_BUFFER_SIZE];

  /* non blocking check on helper logging pipe */
  struct pollfd fds = {
      .fd = g_configuration->helper_pipes[0], .events = POLLIN,
  };
  int data_avail = poll(&fds, 1, 0);
  if (data_avail < 0) {
    char errbuf[ERR_BUF_SIZE];
    if (errno != EINTR || errno != EAGAIN)
      ERROR("dpdkstats: poll(2) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }
  while (data_avail) {
    int nbytes = read(g_configuration->helper_pipes[0], buf, sizeof(buf));
    if (nbytes <= 0)
      break;
    ssnprintf(out, nbytes, "%s", buf);
    DEBUG("dpdkstat: helper-proc: %s", out);
  }

  if (respawn_helper) {
    if (g_configuration->helper_pid)
      dpdk_helper_stop(RESET);
    dpdk_helper_spawn(DPDK_HELPER_ACTION_COUNT_STATS);
  }

  /* Kick helper process through SHM */
  sem_post(&g_configuration->sema_helper_get_stats);

  cdtime_t now = cdtime();
  ret = sem_timedwait(&g_configuration->sema_stats_in_shm,
                      &CDTIME_T_TO_TIMESPEC(now + g_configuration->interval));
  if (ret == -1) {
    if (errno == ETIMEDOUT)
      DEBUG(
          "dpdkstat: timeout in collectd thread: is a DPDK Primary running? ");
    return 0;
  }

  /* Dispatch the stats.*/
  uint32_t count = 0, port_num = 0;

  for (uint32_t i = 0; i < g_configuration->num_ports; i++) {
    char dev_name[64];
    cdtime_t port_read_time = g_configuration->port_read_time[i];
    uint32_t counters_num = g_configuration->num_stats_in_port[i];
    size_t ports_max = CHAR_BIT * sizeof(g_configuration->enabled_port_mask);
    for (size_t j = port_num; j < ports_max; j++) {
      if ((g_configuration->enabled_port_mask & (1 << j)) != 0)
        break;
      port_num++;
    }

    if (g_configuration->port_name[i][0] != 0)
      ssnprintf(dev_name, sizeof(dev_name), "%s",
                g_configuration->port_name[i]);
    else
      ssnprintf(dev_name, sizeof(dev_name), "port.%" PRIu32, port_num);
    dpdk_submit_xstats(dev_name, count, counters_num, port_read_time);
    count += counters_num;
    port_num++;
  } /* for each port */
  return 0;
}