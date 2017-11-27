static int dpdk_helper_run(void) {
  char errbuf[ERR_BUF_SIZE];
  pid_t ppid = getppid();
  g_configuration->helper_status = DPDK_HELPER_WAITING_ON_PRIMARY;

  while (1) {
    /* sem_timedwait() to avoid blocking forever */
    cdtime_t now = cdtime();
    cdtime_t safety_period = MS_TO_CDTIME_T(1500);
    int ret =
        sem_timedwait(&g_configuration->sema_helper_get_stats,
                      &CDTIME_T_TO_TIMESPEC(now + safety_period +
                                            g_configuration->interval * 2));

    if (ret == -1 && errno == ETIMEDOUT) {
      ERROR("dpdkstat-helper: sem timedwait()"
            " timeout, did collectd terminate?");
      dpdk_helper_stop(RESET);
    }
    /* Parent PID change means collectd died so quit the helper process. */
    if (ppid != getppid()) {
      WARNING("dpdkstat-helper: parent PID changed, quitting.");
      dpdk_helper_stop(RESET);
    }

    /* Checking for DPDK primary process. */
    if (!rte_eal_primary_proc_alive(g_configuration->file_prefix)) {
      if (g_configuration->eal_initialized) {
        WARNING("dpdkstat-helper: no primary alive but EAL initialized:"
                " quitting.");
        dpdk_helper_stop(RESET);
      }
      g_configuration->helper_status = DPDK_HELPER_WAITING_ON_PRIMARY;
      /* Back to start of while() - waiting for primary process */
      continue;
    }

    if (!g_configuration->eal_initialized) {
      /* Initialize EAL. */
      int ret = dpdk_helper_init_eal();
      if (ret != 0) {
        WARNING("ERROR INITIALIZING EAL");
        dpdk_helper_stop(RESET);
      }
    }

    g_configuration->helper_status = DPDK_HELPER_ALIVE_SENDING_STATS;

    uint8_t nb_ports = rte_eth_dev_count();
    if (nb_ports == 0) {
      DEBUG("dpdkstat-helper: No DPDK ports available. "
            "Check bound devices to DPDK driver.");
      dpdk_helper_stop(RESET);
    }

    if (nb_ports > RTE_MAX_ETHPORTS)
      nb_ports = RTE_MAX_ETHPORTS;

    int len = 0, enabled_port_count = 0, num_xstats = 0;
    for (uint8_t i = 0; i < nb_ports; i++) {
      if (!(g_configuration->enabled_port_mask & (1 << i)))
        continue;

      if (g_configuration->helper_action == DPDK_HELPER_ACTION_COUNT_STATS) {
#if RTE_VERSION >= RTE_VERSION_16_07
        len = rte_eth_xstats_get_names(i, NULL, 0);
#else
        len = rte_eth_xstats_get(i, NULL, 0);
#endif
        if (len < 0) {
          ERROR("dpdkstat-helper: Cannot get xstats count on port %" PRIu8, i);
          break;
        }
        num_xstats += len;
        g_configuration->num_stats_in_port[enabled_port_count] = len;
        enabled_port_count++;
        continue;
      } else {
        len = g_configuration->num_stats_in_port[enabled_port_count];
        g_configuration->port_read_time[enabled_port_count] = cdtime();
        ret = rte_eth_xstats_get(
            i, g_configuration->xstats + num_xstats,
            g_configuration->num_stats_in_port[enabled_port_count]);
        if (ret < 0 || ret != len) {
          DEBUG("dpdkstat-helper: Error reading xstats on port %" PRIu8
                " len = %d",
                i, len);
          break;
        }
#if RTE_VERSION >= RTE_VERSION_16_07
        ret = rte_eth_xstats_get_names(i, g_configuration->xnames + num_xstats,
                                       len);
        if (ret < 0 || ret != len) {
          ERROR("dpdkstat-helper: Error reading xstat names (port=%d; len=%d)",
                i, len);
          break;
        }
#endif
        num_xstats += g_configuration->num_stats_in_port[enabled_port_count];
        enabled_port_count++;
      }
    } /* for (nb_ports) */

    if (g_configuration->helper_action == DPDK_HELPER_ACTION_COUNT_STATS) {
      g_configuration->num_ports = enabled_port_count;
      g_configuration->num_xstats = num_xstats;
      DEBUG("dpdkstat-helper ports: %" PRIu32 ", num stats: %" PRIu32,
            g_configuration->num_ports, g_configuration->num_xstats);
      /* Exit, allowing collectd to re-init SHM to the right size */
      g_configuration->collectd_reinit_shm = REINIT_SHM;
      dpdk_helper_stop(NO_RESET);
    }
    /* Now kick collectd send thread to send the stats */
    int err = sem_post(&g_configuration->sema_stats_in_shm);
    if (err) {
      WARNING("dpdkstat: error posting semaphore to helper %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
      dpdk_helper_stop(RESET);
    }
  } /* while(1) */

  return 0;
}