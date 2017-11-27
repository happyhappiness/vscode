static int ethstat_read_interface(char *device) {
  int fd;
  struct ethtool_gstrings *strings;
  struct ethtool_stats *stats;
  size_t n_stats;
  size_t strings_size;
  size_t stats_size;
  int status;

  fd = socket(AF_INET, SOCK_DGRAM, /* protocol = */ 0);
  if (fd < 0) {
    char errbuf[1024];
    ERROR("ethstat plugin: Failed to open control socket: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  struct ethtool_drvinfo drvinfo = {.cmd = ETHTOOL_GDRVINFO};

  struct ifreq req = {.ifr_data = (void *)&drvinfo};

  sstrncpy(req.ifr_name, device, sizeof(req.ifr_name));

  status = ioctl(fd, SIOCETHTOOL, &req);
  if (status < 0) {
    char errbuf[1024];
    close(fd);
    ERROR("ethstat plugin: Failed to get driver information "
          "from %s: %s",
          device, sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  n_stats = (size_t)drvinfo.n_stats;
  if (n_stats < 1) {
    close(fd);
    ERROR("ethstat plugin: No stats available for %s", device);
    return (-1);
  }

  strings_size = sizeof(struct ethtool_gstrings) + (n_stats * ETH_GSTRING_LEN);
  stats_size = sizeof(struct ethtool_stats) + (n_stats * sizeof(uint64_t));

  strings = malloc(strings_size);
  stats = malloc(stats_size);
  if ((strings == NULL) || (stats == NULL)) {
    close(fd);
    sfree(strings);
    sfree(stats);
    ERROR("ethstat plugin: malloc failed.");
    return (-1);
  }

  strings->cmd = ETHTOOL_GSTRINGS;
  strings->string_set = ETH_SS_STATS;
  strings->len = n_stats;
  req.ifr_data = (void *)strings;
  status = ioctl(fd, SIOCETHTOOL, &req);
  if (status < 0) {
    char errbuf[1024];
    close(fd);
    free(strings);
    free(stats);
    ERROR("ethstat plugin: Cannot get strings from %s: %s", device,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  stats->cmd = ETHTOOL_GSTATS;
  stats->n_stats = n_stats;
  req.ifr_data = (void *)stats;
  status = ioctl(fd, SIOCETHTOOL, &req);
  if (status < 0) {
    char errbuf[1024];
    close(fd);
    free(strings);
    free(stats);
    ERROR("ethstat plugin: Reading statistics from %s failed: %s", device,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  for (size_t i = 0; i < n_stats; i++) {
    char *stat_name;

    stat_name = (void *)&strings->data[i * ETH_GSTRING_LEN];
    /* Remove leading spaces in key name */
    while (isspace((int)*stat_name))
      stat_name++;

    DEBUG("ethstat plugin: device = \"%s\": %s = %" PRIu64, device, stat_name,
          (uint64_t)stats->data[i]);
    ethstat_submit_value(device, stat_name, (derive_t)stats->data[i]);
  }

  close(fd);
  sfree(strings);
  sfree(stats);

  return (0);
}