uint8_t dpdk_helper_eth_dev_count() {
  uint8_t ports = rte_eth_dev_count();
  if (ports == 0) {
    ERROR(
        "%s:%d: No DPDK ports available. Check bound devices to DPDK driver.\n",
        __FUNCTION__, __LINE__);
    return ports;
  }

  if (ports > RTE_MAX_ETHPORTS) {
    ERROR("%s:%d: Number of DPDK ports (%u) is greater than "
          "RTE_MAX_ETHPORTS=%d. Ignoring extra ports\n",
          __FUNCTION__, __LINE__, ports, RTE_MAX_ETHPORTS);
    ports = RTE_MAX_ETHPORTS;
  }

  return ports;
}