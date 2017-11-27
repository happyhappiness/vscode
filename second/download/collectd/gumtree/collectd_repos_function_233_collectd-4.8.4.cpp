static int ping_config (const char *key, const char *value) /* {{{ */
{
  if (strcasecmp (key, "Host") == 0)
  {
    hostlist_t *hl;
    char *host;

    hl = (hostlist_t *) malloc (sizeof (hostlist_t));
    if (hl == NULL)
    {
      char errbuf[1024];
      ERROR ("ping plugin: malloc failed: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      return (1);
    }

    host = strdup (value);
    if (host == NULL)
    {
      char errbuf[1024];
      sfree (hl);
      ERROR ("ping plugin: strdup failed: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      return (1);
    }

    hl->host = host;
    hl->pkg_sent = 0;
    hl->pkg_recv = 0;
    hl->latency_total = 0.0;
    hl->latency_squared = 0.0;
    hl->next = hostlist_head;
    hostlist_head = hl;
  }
  else if (strcasecmp (key, "TTL") == 0)
  {
    int ttl = atoi (value);
    if ((ttl > 0) && (ttl <= 255))
      ping_ttl = ttl;
    else
      WARNING ("ping plugin: Ignoring invalid TTL %i.", ttl);
  }
  else if (strcasecmp (key, "Interval") == 0)
  {
    double tmp;

    tmp = atof (value);
    if (tmp > 0.0)
      ping_interval = tmp;
    else
      WARNING ("ping plugin: Ignoring invalid interval %g (%s)",
          tmp, value);
  }
  else if (strcasecmp (key, "Timeout") == 0)
  {
    double tmp;

    tmp = atof (value);
    if (tmp > 0.0)
      ping_timeout = tmp;
    else
      WARNING ("ping plugin: Ignoring invalid timeout %g (%s)",
          tmp, value);
  }
  else
  {
    return (-1);
  }

  return (0);
}