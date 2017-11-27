static int dns_init(void) {
  /* clean up an old thread */
  int status;

  pthread_mutex_lock(&traffic_mutex);
  tr_queries = 0;
  tr_responses = 0;
  pthread_mutex_unlock(&traffic_mutex);

  if (listen_thread_init != 0)
    return (-1);

  status = plugin_thread_create(&listen_thread, NULL, dns_child_loop, (void *)0,
                                "dns listen");
  if (status != 0) {
    char errbuf[1024];
    ERROR("dns plugin: pthread_create failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  listen_thread_init = 1;

#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_NET_RAW)
  if (check_capability(CAP_NET_RAW) != 0) {
    if (getuid() == 0)
      WARNING("dns plugin: Running collectd as root, but the CAP_NET_RAW "
              "capability is missing. The plugin's read function will probably "
              "fail. Is your init system dropping capabilities?");
    else
      WARNING("dns plugin: collectd doesn't have the CAP_NET_RAW capability. "
              "If you don't want to run collectd as root, try running \"setcap "
              "cap_net_raw=ep\" on the collectd binary.");
  }
#endif

  return (0);
}