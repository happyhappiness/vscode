static void dpdk_events_keep_alive_dispatch(dpdk_helper_ctx_t *phc) {
  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(phc);

  /* dispatch Keep Alive values to collectd */
  for (int i = 0; i < RTE_KEEPALIVE_MAXCORES; i++) {
    if (i < INT64_BIT_SIZE) {
      if (!(ec->config.keep_alive.lcore_mask.low & ((uint64_t)1 << i)))
        continue;
    } else if (i >= INT64_BIT_SIZE && i < INT64_BIT_SIZE * 2) {
      if (!(ec->config.keep_alive.lcore_mask.high &
            ((uint64_t)1 << (i - INT64_BIT_SIZE))))
        continue;
    } else {
      WARNING(DPDK_EVENTS_PLUGIN
              ": %s:%d Core id %u is out of 0 to %u range, skipping",
              __FUNCTION__, __LINE__, i, INT64_BIT_SIZE * 2);
      continue;
    }

    char core_name[DATA_MAX_NAME_LEN];
    snprintf(core_name, sizeof(core_name), "lcore%u", i);

    if (!ec->config.keep_alive.send_updated ||
        (ec->core_info[i].lcore_state !=
         ec->config.keep_alive.shm->core_state[i])) {
      ec->core_info[i].lcore_state = ec->config.keep_alive.shm->core_state[i];
      ec->core_info[i].read_time = cdtime();

      if (ec->config.keep_alive.notify) {
        char msg[DATA_MAX_NAME_LEN];
        int sev;

        switch (ec->config.keep_alive.shm->core_state[i]) {
        case RTE_KA_STATE_ALIVE:
          sev = NOTIF_OKAY;
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: ALIVE", i);
          break;
        case RTE_KA_STATE_MISSING:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: MISSING", i);
          sev = NOTIF_WARNING;
          break;
        case RTE_KA_STATE_DEAD:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: DEAD", i);
          sev = NOTIF_FAILURE;
          break;
        case RTE_KA_STATE_UNUSED:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: UNUSED", i);
          sev = NOTIF_OKAY;
          break;
        case RTE_KA_STATE_GONE:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: GONE", i);
          sev = NOTIF_FAILURE;
          break;
        case RTE_KA_STATE_DOZING:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: DOZING", i);
          sev = NOTIF_OKAY;
          break;
        case RTE_KA_STATE_SLEEP:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: SLEEP", i);
          sev = NOTIF_OKAY;
          break;
        default:
          snprintf(msg, sizeof(msg), "lcore %u Keep Alive Status: UNKNOWN", i);
          sev = NOTIF_FAILURE;
        }

        dpdk_events_notification_dispatch(sev, KEEPALIVE_PLUGIN_INSTANCE,
                                          ec->core_info[i].read_time, msg);
      } else {
        dpdk_events_gauge_submit(KEEPALIVE_PLUGIN_INSTANCE, core_name,
                                 ec->config.keep_alive.shm->core_state[i],
                                 ec->core_info[i].read_time);
      }
    }
  }
}