static int get_if_dev_stats(struct interface_device *if_dev) {
  virDomainInterfaceStatsStruct stats = {0};
  char *display_name = NULL;

  if (!if_dev) {
    ERROR(PLUGIN_NAME " plugin: get_if_dev_stats: NULL pointer");
    return -1;
  }

  switch (interface_format) {
  case if_address:
    display_name = if_dev->address;
    break;
  case if_number:
    display_name = if_dev->number;
    break;
  case if_name:
  default:
    display_name = if_dev->path;
  }

  if (virDomainInterfaceStats(if_dev->dom, if_dev->path, &stats,
                              sizeof(stats)) != 0) {
    ERROR(PLUGIN_NAME " plugin: virDomainInterfaceStats failed");
    return -1;
  }

  if ((stats.rx_bytes != -1) && (stats.tx_bytes != -1))
    submit_derive2("if_octets", (derive_t)stats.rx_bytes,
                   (derive_t)stats.tx_bytes, if_dev->dom, display_name);

  if ((stats.rx_packets != -1) && (stats.tx_packets != -1))
    submit_derive2("if_packets", (derive_t)stats.rx_packets,
                   (derive_t)stats.tx_packets, if_dev->dom, display_name);

  if ((stats.rx_errs != -1) && (stats.tx_errs != -1))
    submit_derive2("if_errors", (derive_t)stats.rx_errs,
                   (derive_t)stats.tx_errs, if_dev->dom, display_name);

  if ((stats.rx_drop != -1) && (stats.tx_drop != -1))
    submit_derive2("if_dropped", (derive_t)stats.rx_drop,
                   (derive_t)stats.tx_drop, if_dev->dom, display_name);
  return 0;
}