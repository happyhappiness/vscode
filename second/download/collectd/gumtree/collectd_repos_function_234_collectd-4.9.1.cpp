static void *ping_thread (void *arg) /* {{{ */
{
  static pingobj_t *pingobj = NULL;

  struct timeval  tv_begin;
  struct timeval  tv_end;
  struct timespec ts_wait;
  struct timespec ts_int;

  hostlist_t *hl;
  int count;

  pthread_mutex_lock (&ping_lock);

  pingobj = ping_construct ();
  if (pingobj == NULL)
  {
    ERROR ("ping plugin: ping_construct failed.");
    ping_thread_error = 1;
    pthread_mutex_unlock (&ping_lock);
    return ((void *) -1);
  }

  if (ping_source != NULL)
    if (ping_setopt (pingobj, PING_OPT_SOURCE, (void *) ping_source) != 0)
      ERROR ("ping plugin: Failed to set source address: %s",
          ping_get_error (pingobj));

#ifdef HAVE_OPING_1_3
  if (ping_device != NULL)
    if (ping_setopt (pingobj, PING_OPT_DEVICE, (void *) ping_device) != 0)
      ERROR ("ping plugin: Failed to set device: %s",
          ping_get_error (pingobj));
#endif

  ping_setopt (pingobj, PING_OPT_TIMEOUT, (void *) &ping_timeout);
  ping_setopt (pingobj, PING_OPT_TTL, (void *) &ping_ttl);

  /* Add all the hosts to the ping object. */
  count = 0;
  for (hl = hostlist_head; hl != NULL; hl = hl->next)
  {
    int status;
    status = ping_host_add (pingobj, hl->host);
    if (status != 0)
      WARNING ("ping plugin: ping_host_add (%s) failed.", hl->host);
    else
      count++;
  }

  if (count == 0)
  {
    ERROR ("ping plugin: No host could be added to ping object. Giving up.");
    ping_thread_error = 1;
    pthread_mutex_unlock (&ping_lock);
    return ((void *) -1);
  }

  /* Set up `ts_int' */
  {
    double temp_sec;
    double temp_nsec;

    temp_nsec = modf (ping_interval, &temp_sec);
    ts_int.tv_sec  = (time_t) temp_sec;
    ts_int.tv_nsec = (long) (temp_nsec * 1000000000L);
  }

  while (ping_thread_loop > 0)
  {
    pingobj_iter_t *iter;
    int status;

    if (gettimeofday (&tv_begin, NULL) < 0)
    {
      ERROR ("ping plugin: gettimeofday failed");
      ping_thread_error = 1;
      break;
    }

    pthread_mutex_unlock (&ping_lock);

    status = ping_send (pingobj);
    if (status < 0)
    {
      ERROR ("ping plugin: ping_send failed: %s", ping_get_error (pingobj));
      pthread_mutex_lock (&ping_lock);
      ping_thread_error = 1;
      break;
    }

    pthread_mutex_lock (&ping_lock);

    if (ping_thread_loop <= 0)
      break;

    for (iter = ping_iterator_get (pingobj);
        iter != NULL;
        iter = ping_iterator_next (iter))
    { /* {{{ */
      char userhost[NI_MAXHOST];
      double latency;
      size_t param_size;

      param_size = sizeof (userhost);
      status = ping_iterator_get_info (iter,
#ifdef PING_INFO_USERNAME
          PING_INFO_USERNAME,
#else
          PING_INFO_HOSTNAME,
#endif
          userhost, &param_size);
      if (status != 0)
      {
        WARNING ("ping plugin: ping_iterator_get_info failed: %s",
            ping_get_error (pingobj));
        continue;
      }

      for (hl = hostlist_head; hl != NULL; hl = hl->next)
        if (strcmp (userhost, hl->host) == 0)
          break;

      if (hl == NULL)
      {
        WARNING ("ping plugin: Cannot find host %s.", userhost);
        continue;
      }

      param_size = sizeof (latency);
      status = ping_iterator_get_info (iter, PING_INFO_LATENCY,
          (void *) &latency, &param_size);
      if (status != 0)
      {
        WARNING ("ping plugin: ping_iterator_get_info failed: %s",
            ping_get_error (pingobj));
        continue;
      }

      hl->pkg_sent++;
      if (latency >= 0.0)
      {
        hl->pkg_recv++;
        hl->latency_total += latency;
        hl->latency_squared += (latency * latency);

        /* reset missed packages counter */
        hl->pkg_missed = 0;
      } else
        hl->pkg_missed++;

      /* if the host did not answer our last N packages, trigger a resolv. */
      if (ping_max_missed >= 0 && hl->pkg_missed >= ping_max_missed)
      { /* {{{ */
        /* we reset the missed package counter here, since we only want to
         * trigger a resolv every N packages and not every package _AFTER_ N
         * missed packages */
        hl->pkg_missed = 0;

        WARNING ("ping plugin: host %s has not answered %d PING requests,"
          " triggering resolve", hl->host, ping_max_missed);

        /* we trigger the resolv simply be removeing and adding the host to our
         * ping object */
        status = ping_host_remove (pingobj, hl->host);
        if (status != 0)
        {
          WARNING ("ping plugin: ping_host_remove (%s) failed.", hl->host);
        }
        else
        {
          status = ping_host_add (pingobj, hl->host);
          if (status != 0)
            WARNING ("ping plugin: ping_host_add (%s) failed.", hl->host);
        }
      } /* }}} ping_max_missed */
    } /* }}} for (iter) */

    if (gettimeofday (&tv_end, NULL) < 0)
    {
      ERROR ("ping plugin: gettimeofday failed");
      ping_thread_error = 1;
      break;
    }

    /* Calculate the absolute time until which to wait and store it in
     * `ts_wait'. */
    time_calc (&ts_wait, &ts_int, &tv_begin, &tv_end);

    status = pthread_cond_timedwait (&ping_cond, &ping_lock, &ts_wait);
    if (ping_thread_loop <= 0)
      break;
  } /* while (ping_thread_loop > 0) */

  pthread_mutex_unlock (&ping_lock);
  ping_destroy (pingobj);

  return ((void *) 0);
}