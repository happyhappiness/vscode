static void *ping_thread(void *arg) /* {{{ */
{
  pingobj_t *pingobj = NULL;

  struct timeval tv_begin;
  struct timeval tv_end;
  struct timespec ts_wait;
  struct timespec ts_int;

  int count;

  c_complain_t complaint = C_COMPLAIN_INIT_STATIC;

  pthread_mutex_lock(&ping_lock);

  pingobj = ping_construct();
  if (pingobj == NULL) {
    ERROR("ping plugin: ping_construct failed.");
    ping_thread_error = 1;
    pthread_mutex_unlock(&ping_lock);
    return (void *)-1;
  }

  if (ping_source != NULL)
    if (ping_setopt(pingobj, PING_OPT_SOURCE, (void *)ping_source) != 0)
      ERROR("ping plugin: Failed to set source address: %s",
            ping_get_error(pingobj));

#ifdef HAVE_OPING_1_3
  if (ping_device != NULL)
    if (ping_setopt(pingobj, PING_OPT_DEVICE, (void *)ping_device) != 0)
      ERROR("ping plugin: Failed to set device: %s", ping_get_error(pingobj));
#endif

  ping_setopt(pingobj, PING_OPT_TIMEOUT, (void *)&ping_timeout);
  ping_setopt(pingobj, PING_OPT_TTL, (void *)&ping_ttl);

  if (ping_data != NULL)
    ping_setopt(pingobj, PING_OPT_DATA, (void *)ping_data);

  /* Add all the hosts to the ping object. */
  count = 0;
  for (hostlist_t *hl = hostlist_head; hl != NULL; hl = hl->next) {
    int tmp_status;
    tmp_status = ping_host_add(pingobj, hl->host);
    if (tmp_status != 0)
      WARNING("ping plugin: ping_host_add (%s) failed: %s", hl->host,
              ping_get_error(pingobj));
    else
      count++;
  }

  if (count == 0) {
    ERROR("ping plugin: No host could be added to ping object. Giving up.");
    ping_thread_error = 1;
    pthread_mutex_unlock(&ping_lock);
    return (void *)-1;
  }

  /* Set up `ts_int' */
  {
    double temp_sec;
    double temp_nsec;

    temp_nsec = modf(ping_interval, &temp_sec);
    ts_int.tv_sec = (time_t)temp_sec;
    ts_int.tv_nsec = (long)(temp_nsec * 1000000000L);
  }

  while (ping_thread_loop > 0) {
    int status;
    _Bool send_successful = 0;

    if (gettimeofday(&tv_begin, NULL) < 0) {
      char errbuf[1024];
      ERROR("ping plugin: gettimeofday failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      ping_thread_error = 1;
      break;
    }

    pthread_mutex_unlock(&ping_lock);

    status = ping_send(pingobj);
    if (status < 0) {
      c_complain(LOG_ERR, &complaint, "ping plugin: ping_send failed: %s",
                 ping_get_error(pingobj));
    } else {
      c_release(LOG_NOTICE, &complaint, "ping plugin: ping_send succeeded.");
      send_successful = 1;
    }

    pthread_mutex_lock(&ping_lock);

    if (ping_thread_loop <= 0)
      break;

    if (send_successful)
      (void)ping_dispatch_all(pingobj);

    if (gettimeofday(&tv_end, NULL) < 0) {
      char errbuf[1024];
      ERROR("ping plugin: gettimeofday failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      ping_thread_error = 1;
      break;
    }

    /* Calculate the absolute time until which to wait and store it in
     * `ts_wait'. */
    time_calc(&ts_wait, &ts_int, &tv_begin, &tv_end);

    pthread_cond_timedwait(&ping_cond, &ping_lock, &ts_wait);
    if (ping_thread_loop <= 0)
      break;
  } /* while (ping_thread_loop > 0) */

  pthread_mutex_unlock(&ping_lock);
  ping_destroy(pingobj);

  return (void *)0;
}