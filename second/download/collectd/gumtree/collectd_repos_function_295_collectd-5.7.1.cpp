static int ping_dispatch_all(pingobj_t *pingobj) /* {{{ */
{
  hostlist_t *hl;
  int status;

  for (pingobj_iter_t *iter = ping_iterator_get(pingobj); iter != NULL;
       iter = ping_iterator_next(iter)) { /* {{{ */
    char userhost[NI_MAXHOST];
    double latency;
    size_t param_size;

    param_size = sizeof(userhost);
    status = ping_iterator_get_info(iter,
#ifdef PING_INFO_USERNAME
                                    PING_INFO_USERNAME,
#else
                                    PING_INFO_HOSTNAME,
#endif
                                    userhost, &param_size);
    if (status != 0) {
      WARNING("ping plugin: ping_iterator_get_info failed: %s",
              ping_get_error(pingobj));
      continue;
    }

    for (hl = hostlist_head; hl != NULL; hl = hl->next)
      if (strcmp(userhost, hl->host) == 0)
        break;

    if (hl == NULL) {
      WARNING("ping plugin: Cannot find host %s.", userhost);
      continue;
    }

    param_size = sizeof(latency);
    status = ping_iterator_get_info(iter, PING_INFO_LATENCY, (void *)&latency,
                                    &param_size);
    if (status != 0) {
      WARNING("ping plugin: ping_iterator_get_info failed: %s",
              ping_get_error(pingobj));
      continue;
    }

    hl->pkg_sent++;
    if (latency >= 0.0) {
      hl->pkg_recv++;
      hl->latency_total += latency;
      hl->latency_squared += (latency * latency);

      /* reset missed packages counter */
      hl->pkg_missed = 0;
    } else
      hl->pkg_missed++;

    /* if the host did not answer our last N packages, trigger a resolv. */
    if ((ping_max_missed >= 0) &&
        (hl->pkg_missed >= ((uint32_t)ping_max_missed))) { /* {{{ */
      /* we reset the missed package counter here, since we only want to
       * trigger a resolv every N packages and not every package _AFTER_ N
       * missed packages */
      hl->pkg_missed = 0;

      WARNING("ping plugin: host %s has not answered %d PING requests,"
              " triggering resolve",
              hl->host, ping_max_missed);

      /* we trigger the resolv simply be removeing and adding the host to our
       * ping object */
      status = ping_host_remove(pingobj, hl->host);
      if (status != 0) {
        WARNING("ping plugin: ping_host_remove (%s) failed.", hl->host);
      } else {
        status = ping_host_add(pingobj, hl->host);
        if (status != 0)
          ERROR("ping plugin: ping_host_add (%s) failed.", hl->host);
      }
    } /* }}} ping_max_missed */
  }   /* }}} for (iter) */

  return (0);
}