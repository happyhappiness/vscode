static int link_filter (const struct sockaddr_nl *sa,
    struct nlmsghdr *nmh, void *args)
{
  struct ifinfomsg *msg;
  int msg_len;
  struct rtattr *attrs[IFLA_MAX + 1];
  struct rtnl_link_stats *stats;

  const char *dev;

  if (nmh->nlmsg_type != RTM_NEWLINK)
  {
    ERROR ("netlink plugin: link_filter: Don't know how to handle type %i.",
	nmh->nlmsg_type);
    return (-1);
  }

  msg = NLMSG_DATA (nmh);

  msg_len = nmh->nlmsg_len - sizeof (struct ifinfomsg);
  if (msg_len < 0)
  {
    ERROR ("netlink plugin: link_filter: msg_len = %i < 0;", msg_len);
    return (-1);
  }

  memset (attrs, '\0', sizeof (attrs));
  if (parse_rtattr (attrs, IFLA_MAX, IFLA_RTA (msg), msg_len) != 0)
  {
    ERROR ("netlink plugin: link_filter: parse_rtattr failed.");
    return (-1);
  }

  if (attrs[IFLA_IFNAME] == NULL)
  {
    ERROR ("netlink plugin: link_filter: attrs[IFLA_IFNAME] == NULL");
    return (-1);
  }
  dev = RTA_DATA (attrs[IFLA_IFNAME]);

  /* Update the `iflist'. It's used to know which interfaces exist and query
   * them later for qdiscs and classes. */
  if (msg->ifi_index >= iflist_len)
  {
    char **temp;

    temp = (char **) realloc (iflist, (msg->ifi_index + 1) * sizeof (char *));
    if (temp == NULL)
    {
      ERROR ("netlink plugin: link_filter: realloc failed.");
      return (-1);
    }

    memset (temp + iflist_len, '\0',
	(msg->ifi_index + 1 - iflist_len) * sizeof (char *));
    iflist = temp;
    iflist_len = msg->ifi_index + 1;
  }
  if ((iflist[msg->ifi_index] == NULL)
      || (strcmp (iflist[msg->ifi_index], dev) != 0))
  {
    sfree (iflist[msg->ifi_index]);
    iflist[msg->ifi_index] = strdup (dev);
  }

  if (attrs[IFLA_STATS] == NULL)
  {
    DEBUG ("netlink plugin: link_filter: No statistics for interface %s.", dev);
    return (0);
  }
  stats = RTA_DATA (attrs[IFLA_STATS]);

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

  return (0);
}