static void check_ignorelist_and_submit (const char *dev,
    struct ir_link_stats_storage_s *stats)
{

  if (check_ignorelist (dev, "interface", NULL) == 0)
  {
    submit_two (dev, "if_octets", NULL, stats->rx_bytes, stats->tx_bytes);
    submit_two (dev, "if_packets", NULL, stats->rx_packets, stats->tx_packets);
    submit_two (dev, "if_errors", NULL, stats->rx_errors, stats->tx_errors);
  }
  else
  {
    DEBUG ("netlink plugin: Ignoring %s/interface.", dev);
  }

  if (check_ignorelist (dev, "if_detail", NULL) == 0)
  {
    submit_two (dev, "if_dropped", NULL, stats->rx_dropped, stats->tx_dropped);
    submit_one (dev, "if_multicast", NULL, stats->multicast);
    submit_one (dev, "if_collisions", NULL, stats->collisions);

    submit_one (dev, "if_rx_errors", "length", stats->rx_length_errors);
    submit_one (dev, "if_rx_errors", "over", stats->rx_over_errors);
    submit_one (dev, "if_rx_errors", "crc", stats->rx_crc_errors);
    submit_one (dev, "if_rx_errors", "frame", stats->rx_frame_errors);
    submit_one (dev, "if_rx_errors", "fifo", stats->rx_fifo_errors);
    submit_one (dev, "if_rx_errors", "missed", stats->rx_missed_errors);

    submit_one (dev, "if_tx_errors", "aborted", stats->tx_aborted_errors);
    submit_one (dev, "if_tx_errors", "carrier", stats->tx_carrier_errors);
    submit_one (dev, "if_tx_errors", "fifo", stats->tx_fifo_errors);
    submit_one (dev, "if_tx_errors", "heartbeat", stats->tx_heartbeat_errors);
    submit_one (dev, "if_tx_errors", "window", stats->tx_window_errors);
  }
  else
  {
    DEBUG ("netlink plugin: Ignoring %s/if_detail.", dev);
  }

}