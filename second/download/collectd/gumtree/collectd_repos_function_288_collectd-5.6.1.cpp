static int ping_read (void) /* {{{ */
{
  if (ping_thread_error != 0)
  {
    ERROR ("ping plugin: The ping thread had a problem. Restarting it.");

    stop_thread ();

    for (hostlist_t *hl = hostlist_head; hl != NULL; hl = hl->next)
    {
      hl->pkg_sent = 0;
      hl->pkg_recv = 0;
      hl->latency_total = 0.0;
      hl->latency_squared = 0.0;
    }

    start_thread ();

    return (-1);
  } /* if (ping_thread_error != 0) */

  for (hostlist_t *hl = hostlist_head; hl != NULL; hl = hl->next) /* {{{ */
  {
    uint32_t pkg_sent;
    uint32_t pkg_recv;
    double latency_total;
    double latency_squared;

    double latency_average;
    double latency_stddev;

    double droprate;

    /* Locking here works, because the structure of the linked list is only
     * changed during configure and shutdown. */
    pthread_mutex_lock (&ping_lock);

    pkg_sent = hl->pkg_sent;
    pkg_recv = hl->pkg_recv;
    latency_total = hl->latency_total;
    latency_squared = hl->latency_squared;

    hl->pkg_sent = 0;
    hl->pkg_recv = 0;
    hl->latency_total = 0.0;
    hl->latency_squared = 0.0;

    pthread_mutex_unlock (&ping_lock);

    /* This e. g. happens when starting up. */
    if (pkg_sent == 0)
    {
      DEBUG ("ping plugin: No packages for host %s have been sent.",
          hl->host);
      continue;
    }

    /* Calculate average. Beware of division by zero. */
    if (pkg_recv == 0)
      latency_average = NAN;
    else
      latency_average = latency_total / ((double) pkg_recv);

    /* Calculate standard deviation. Beware even more of division by zero. */
    if (pkg_recv == 0)
      latency_stddev = NAN;
    else if (pkg_recv == 1)
      latency_stddev = 0.0;
    else
      latency_stddev = sqrt (((((double) pkg_recv) * latency_squared)
          - (latency_total * latency_total))
          / ((double) (pkg_recv * (pkg_recv - 1))));

    /* Calculate drop rate. */
    droprate = ((double) (pkg_sent - pkg_recv)) / ((double) pkg_sent);

    submit (hl->host, "ping", latency_average);
    submit (hl->host, "ping_stddev", latency_stddev);
    submit (hl->host, "ping_droprate", droprate);
  } /* }}} for (hl = hostlist_head; hl != NULL; hl = hl->next) */

  return (0);
}