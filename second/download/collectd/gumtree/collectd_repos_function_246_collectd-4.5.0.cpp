static void *csnmp_read_thread (void *data)
{
  host_definition_t *host;

  pthread_mutex_lock (&host_lock);
  while (do_shutdown == 0)
  {
    pthread_cond_wait (&host_cond, &host_lock);

    for (host = host_head; host != NULL; host = host->next)
    {
      if (do_shutdown != 0)
	break;
      if (host->state != STATE_WAIT)
	continue;

      host->state = STATE_BUSY;
      pthread_mutex_unlock (&host_lock);
      csnmp_read_host (host);
      pthread_mutex_lock (&host_lock);
      host->state = STATE_IDLE;
    } /* for (host) */
  } /* while (do_shutdown == 0) */
  pthread_mutex_unlock (&host_lock);

  pthread_exit ((void *) 0);
  return ((void *) 0);
}