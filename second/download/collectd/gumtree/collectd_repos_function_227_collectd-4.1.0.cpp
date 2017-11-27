static int csnmp_init (void)
{
  host_definition_t *host;
  int i;

  if (host_head == NULL)
    return (-1);

  call_snmp_init_once ();

  threads_num = 0;
  for (host = host_head; host != NULL; host = host->next)
  {
    threads_num++;
    /* We need to initialize `skip_num' here, because `interval_g' isn't
     * initialized during `configure'. */
    host->skip_left = interval_g;
    if (host->skip_num == 0)
    {
      host->skip_num = interval_g;
    }
    else if (host->skip_num < interval_g)
    {
      host->skip_num = interval_g;
      WARNING ("snmp plugin: Data for host `%s' will be collected every %i seconds.",
	  host->name, host->skip_num);
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
    return (-1);
  memset (threads, '\0', threads_num * sizeof (pthread_t));

  for (i = 0; i < threads_num; i++)
      pthread_create (threads + i, NULL, csnmp_read_thread, (void *) 0);

  return (0);
}