static int csnmp_read (void)
{
  host_definition_t *host;
  time_t now;

  if (host_head == NULL)
  {
    INFO ("snmp plugin: No hosts configured.");
    return (-1);
  }

  now = time (NULL);

  pthread_mutex_lock (&host_lock);
  for (host = host_head; host != NULL; host = host->next)
  {
    if (host->state != STATE_IDLE)
      continue;

    host->skip_left -= interval_g;
    if (host->skip_left >= interval_g)
      continue;

    host->state = STATE_WAIT;

    host->skip_left = host->skip_num;
  } /* for (host) */

  pthread_cond_broadcast (&host_cond);
  pthread_mutex_unlock (&host_lock);

  return (0);
}