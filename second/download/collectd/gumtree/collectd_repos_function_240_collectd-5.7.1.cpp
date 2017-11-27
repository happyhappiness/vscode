static int dpdk_helper_stop(int reset) {
  g_configuration->helper_status = DPDK_HELPER_GRACEFUL_QUIT;
  if (reset) {
    g_configuration->eal_initialized = 0;
    g_configuration->num_ports = 0;
    g_configuration->xstats = NULL;
    g_configuration->num_xstats = 0;
    for (int i = 0; i < RTE_MAX_ETHPORTS; i++)
      g_configuration->num_stats_in_port[i] = 0;
  }
  close(g_configuration->helper_pipes[1]);
  int err = kill(g_configuration->helper_pid, SIGKILL);
  if (err) {
    char errbuf[ERR_BUF_SIZE];
    WARNING("dpdkstat: error sending kill to helper: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }

  return 0;
}