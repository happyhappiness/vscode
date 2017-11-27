static int dpdk_events_link_status_dispatch(dpdk_helper_ctx_t *phc) {
  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(phc);
  DEBUG(DPDK_EVENTS_PLUGIN ": %s:%d ports=%u", __FUNCTION__, __LINE__,
        ec->nb_ports);

  /* dispatch Link Status values to collectd */
  for (int i = 0; i < ec->nb_ports; i++) {
    if (ec->config.link_status.enabled_port_mask & (1 << i)) {
      if (!ec->config.link_status.send_updated ||
          ec->link_info[i].status_updated) {

        DEBUG(DPDK_EVENTS_PLUGIN ": Dispatch PORT %d Link Status: %s", i,
              ec->link_info[i].link_status ? "UP" : "DOWN");

        char dev_name[DATA_MAX_NAME_LEN];
        if (ec->config.link_status.port_name[i][0] != 0) {
          snprintf(dev_name, sizeof(dev_name), "%s",
                   ec->config.link_status.port_name[i]);
        } else {
          snprintf(dev_name, sizeof(dev_name), "port.%d", i);
        }

        if (ec->config.link_status.notify) {
          int sev = ec->link_info[i].link_status ? NOTIF_OKAY : NOTIF_WARNING;
          char msg[DATA_MAX_NAME_LEN];
          snprintf(msg, sizeof(msg), "Link Status: %s",
                   ec->link_info[i].link_status ? "UP" : "DOWN");
          dpdk_events_notification_dispatch(sev, dev_name,
                                            ec->link_info[i].read_time, msg);
        } else {
          dpdk_events_gauge_submit(dev_name, "link_status",
                                   (gauge_t)ec->link_info[i].link_status,
                                   ec->link_info[i].read_time);
        }
        ec->link_info[i].status_updated = 0;
      }
    }
  }

  return 0;
}