static void dpdk_submit_xstats(const char *dev_name, int count,
                               uint32_t counters, cdtime_t port_read_time) {
  for (uint32_t j = 0; j < counters; j++) {
    value_list_t vl = VALUE_LIST_INIT;
    char *counter_name;
    char *type_end;

    vl.values = &(value_t){.derive = (derive_t)DPDK_STATS_XSTAT_GET_VALUE(
                               g_configuration, count + j)};
    vl.values_len = 1; /* Submit stats one at a time */
    vl.time = port_read_time;
    sstrncpy(vl.plugin, "dpdkstat", sizeof(vl.plugin));
    sstrncpy(vl.plugin_instance, dev_name, sizeof(vl.plugin_instance));
    counter_name = DPDK_STATS_XSTAT_GET_NAME(g_configuration, count + j);
    if (counter_name == NULL) {
      WARNING("dpdkstat: Failed to get counter name.");
      return;
    }

    type_end = strrchr(counter_name, '_');

    if ((type_end != NULL) &&
        (strncmp(counter_name, "rx_", strlen("rx_")) == 0)) {
      if (strncmp(type_end, "_errors", strlen("_errors")) == 0) {
        sstrncpy(vl.type, "if_rx_errors", sizeof(vl.type));
      } else if (strncmp(type_end, "_dropped", strlen("_dropped")) == 0) {
        sstrncpy(vl.type, "if_rx_dropped", sizeof(vl.type));
      } else if (strncmp(type_end, "_bytes", strlen("_bytes")) == 0) {
        sstrncpy(vl.type, "if_rx_octets", sizeof(vl.type));
      } else if (strncmp(type_end, "_packets", strlen("_packets")) == 0) {
        sstrncpy(vl.type, "if_rx_packets", sizeof(vl.type));
      } else if (strncmp(type_end, "_placement", strlen("_placement")) == 0) {
        sstrncpy(vl.type, "if_rx_errors", sizeof(vl.type));
      } else if (strncmp(type_end, "_buff", strlen("_buff")) == 0) {
        sstrncpy(vl.type, "if_rx_errors", sizeof(vl.type));
      } else {
        /* Does not fit obvious type: use a more generic one */
        sstrncpy(vl.type, "derive", sizeof(vl.type));
      }

    } else if ((type_end != NULL) &&
               (strncmp(counter_name, "tx_", strlen("tx_"))) == 0) {
      if (strncmp(type_end, "_errors", strlen("_errors")) == 0) {
        sstrncpy(vl.type, "if_tx_errors", sizeof(vl.type));
      } else if (strncmp(type_end, "_dropped", strlen("_dropped")) == 0) {
        sstrncpy(vl.type, "if_tx_dropped", sizeof(vl.type));
      } else if (strncmp(type_end, "_bytes", strlen("_bytes")) == 0) {
        sstrncpy(vl.type, "if_tx_octets", sizeof(vl.type));
      } else if (strncmp(type_end, "_packets", strlen("_packets")) == 0) {
        sstrncpy(vl.type, "if_tx_packets", sizeof(vl.type));
      } else {
        /* Does not fit obvious type: use a more generic one */
        sstrncpy(vl.type, "derive", sizeof(vl.type));
      }
    } else if ((type_end != NULL) &&
               (strncmp(counter_name, "flow_", strlen("flow_"))) == 0) {

      if (strncmp(type_end, "_filters", strlen("_filters")) == 0) {
        sstrncpy(vl.type, "operations", sizeof(vl.type));
      } else if (strncmp(type_end, "_errors", strlen("_errors")) == 0) {
        sstrncpy(vl.type, "errors", sizeof(vl.type));
      } else if (strncmp(type_end, "_filters", strlen("_filters")) == 0) {
        sstrncpy(vl.type, "filter_result", sizeof(vl.type));
      }
    } else if ((type_end != NULL) &&
               (strncmp(counter_name, "mac_", strlen("mac_"))) == 0) {
      if (strncmp(type_end, "_errors", strlen("_errors")) == 0) {
        sstrncpy(vl.type, "errors", sizeof(vl.type));
      }
    } else {
      /* Does not fit obvious type, or strrchr error:
       *   use a more generic type */
      sstrncpy(vl.type, "derive", sizeof(vl.type));
    }

    sstrncpy(vl.type_instance, counter_name, sizeof(vl.type_instance));
    plugin_dispatch_values(&vl);
  }
}