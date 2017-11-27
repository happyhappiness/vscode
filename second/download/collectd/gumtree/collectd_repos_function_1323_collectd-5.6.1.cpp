static int plugin_init (void) /* {{{ */
{
  int status;

  if (stat_nodes == NULL)
  {
    /* Collect the "total" data by default. */
    service_statnode_add ("total",
        /* host   = */ NULL,
        /* server = */ NULL,
        /* script = */ NULL);
  }

  if (collector_thread_running)
    return (0);

  status = plugin_thread_create (&collector_thread_id,
      /* attrs = */ NULL,
      collector_thread,
      /* args = */ NULL);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("pinba plugin: pthread_create(3) failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }
  collector_thread_running = 1;

  return (0);
}