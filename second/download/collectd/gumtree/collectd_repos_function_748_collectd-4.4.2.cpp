static void *dispatch_thread (void *arg)
{
  while (42)
  {
    receive_list_entry_t *ent;

    /* Lock and wait for more data to come in */
    pthread_mutex_lock (&receive_list_lock);
    while ((listen_loop == 0)
	&& (receive_list_head == NULL))
      pthread_cond_wait (&receive_list_cond, &receive_list_lock);

    /* Remove the head entry and unlock */
    ent = receive_list_head;
    if (ent != NULL)
      receive_list_head = ent->next;
    pthread_mutex_unlock (&receive_list_lock);

    /* Check whether we are supposed to exit. We do NOT check `listen_loop'
     * because we dispatch all missing packets before shutting down. */
    if (ent == NULL)
      break;

    parse_packet (ent->data, ent->data_len);

    sfree (ent);
  } /* while (42) */

  return (NULL);
}