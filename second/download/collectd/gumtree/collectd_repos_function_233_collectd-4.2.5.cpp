static int csnmp_init (void)
{
  host_definition_t *host;
  int i;

  if (host_head == NULL)
  {
    NOTICE ("snmp plugin: No host has been defined.");
    return (-1);
  }

  call_snmp_init_once ();

  threads_num = 0;
  for (host = host_head; host != NULL; host = host->next)
  {
    threads_num++;
    /* We need to initialize `interval' here, because `interval_g' isn't
     * initialized during `configure'. */
    host->next_update = time (NULL);
    if (host->interval == 0)
    {
      host->interval = interval_g;
    }
    else if (host->interval < interval_g)
    {
      host->interval = interval_g;
      WARNING ("snmp plugin: Data for host `%s' will be collected every %i seconds.",
	  host->name, host->interval);
    }

    csnmp_host_open_session (host);
  } /* for (host) */

  /* Now start the reading threads */
  if (threads_num > 3)
  {
    threads_num = 3 + ((threads_num - 3) / 10);
    if (threads_num > 10)
      threads_num = 10;
  }

  threads = (pthread_t *) malloc (threads_num * sizeof (pthread_t));
  if (threads == NULL)
  {
    ERROR ("snmp plugin: malloc failed.");
    return (-1);
  }
  memset (threads, '\0', threads_num * sizeof (pthread_t));

  for (i = 0; i < threads_num; i++)
      pthread_create (threads + i, NULL, csnmp_read_thread, (void *) 0);

  return (0);
}