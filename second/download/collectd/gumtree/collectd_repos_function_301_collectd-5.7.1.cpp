static int ping_config(const char *key, const char *value) /* {{{ */
{
  if (strcasecmp(key, "Host") == 0) {
    hostlist_t *hl;
    char *host;

    hl = malloc(sizeof(*hl));
    if (hl == NULL) {
      char errbuf[1024];
      ERROR("ping plugin: malloc failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (1);
    }

    host = strdup(value);
    if (host == NULL) {
      char errbuf[1024];
      sfree(hl);
      ERROR("ping plugin: strdup failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (1);
    }

    hl->host = host;
    hl->pkg_sent = 0;
    hl->pkg_recv = 0;
    hl->pkg_missed = 0;
    hl->latency_total = 0.0;
    hl->latency_squared = 0.0;
    hl->next = hostlist_head;
    hostlist_head = hl;
  } else if (strcasecmp(key, "SourceAddress") == 0) {
    int status = config_set_string(key, &ping_source, value);
    if (status != 0)
      return (status);
  }
#ifdef HAVE_OPING_1_3
  else if (strcasecmp(key, "Device") == 0) {
    int status = config_set_string(key, &ping_device, value);
    if (status != 0)
      return (status);
  }
#endif
  else if (strcasecmp(key, "TTL") == 0) {
    int ttl = atoi(value);
    if ((ttl > 0) && (ttl <= 255))
      ping_ttl = ttl;
    else
      WARNING("ping plugin: Ignoring invalid TTL %i.", ttl);
  } else if (strcasecmp(key, "Interval") == 0) {
    double tmp;

    tmp = atof(value);
    if (tmp > 0.0)
      ping_interval = tmp;
    else
      WARNING("ping plugin: Ignoring invalid interval %g (%s)", tmp, value);
  } else if (strcasecmp(key, "Size") == 0) {
    size_t size = (size_t)atoi(value);

    /* Max IP packet size - (IPv6 + ICMP) = 65535 - (40 + 8) = 65487 */
    if (size <= 65487) {
      sfree(ping_data);
      ping_data = malloc(size + 1);
      if (ping_data == NULL) {
        ERROR("ping plugin: malloc failed.");
        return (1);
      }

      /* Note: By default oping is using constant string
       * "liboping -- ICMP ping library <http://octo.it/liboping/>"
       * which is exactly 56 bytes.
       *
       * Optimally we would follow the ping(1) behaviour, but we
       * cannot use byte 00 or start data payload at exactly same
       * location, due to oping library limitations. */
      for (size_t i = 0; i < size; i++) /* {{{ */
      {
        /* This restricts data pattern to be only composed of easily
         * printable characters, and not NUL character. */
        ping_data[i] = ('0' + i % 64);
      } /* }}} for (i = 0; i < size; i++) */
      ping_data[size] = 0;
    } else
      WARNING("ping plugin: Ignoring invalid Size %zu.", size);
  } else if (strcasecmp(key, "Timeout") == 0) {
    double tmp;

    tmp = atof(value);
    if (tmp > 0.0)
      ping_timeout = tmp;
    else
      WARNING("ping plugin: Ignoring invalid timeout %g (%s)", tmp, value);
  } else if (strcasecmp(key, "MaxMissed") == 0) {
    ping_max_missed = atoi(value);
    if (ping_max_missed < 0)
      INFO("ping plugin: MaxMissed < 0, disabled re-resolving of hosts");
  } else {
    return (-1);
  }

  return (0);
}