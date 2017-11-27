static int dpdk_helper_link_status_get(dpdk_helper_ctx_t *phc) {
  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(phc);

  /* get Link Status values from DPDK */
  uint8_t nb_ports = rte_eth_dev_count();
  if (nb_ports == 0) {
    DPDK_CHILD_LOG("dpdkevent-helper: No DPDK ports available. "
                   "Check bound devices to DPDK driver.\n");
    return -ENODEV;
  }
  ec->nb_ports = nb_ports > RTE_MAX_ETHPORTS ? RTE_MAX_ETHPORTS : nb_ports;

  for (int i = 0; i < ec->nb_ports; i++) {
    if (ec->config.link_status.enabled_port_mask & (1 << i)) {
      struct rte_eth_link link;
      ec->link_info[i].read_time = cdtime();
      rte_eth_link_get_nowait(i, &link);
      if ((link.link_status == ETH_LINK_NA) ||
          (link.link_status != ec->link_info[i].link_status)) {
        ec->link_info[i].link_status = link.link_status;
        ec->link_info[i].status_updated = 1;
        DPDK_CHILD_LOG(" === PORT %d Link Status: %s\n", i,
                       link.link_status ? "UP" : "DOWN");
      }
    }
  }

  return 0;
}