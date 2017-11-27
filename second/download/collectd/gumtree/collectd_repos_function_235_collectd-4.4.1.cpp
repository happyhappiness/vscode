static int csnmp_shutdown (void)
{
  host_definition_t *host_this;
  host_definition_t *host_next;

  data_definition_t *data_this;
  data_definition_t *data_next;

  int i;

  pthread_mutex_lock (&host_lock);
  do_shutdown = 1;
  pthread_cond_broadcast (&host_cond);
  pthread_mutex_unlock (&host_lock);

  for (i = 0; i < threads_num; i++)
    pthread_join (threads[i], NULL);

  /* Now that all the threads have exited, let's free all the global variables.
   * This isn't really neccessary, I guess, but I think it's good stile to do
   * so anyway. */
  host_this = host_head;
  host_head = NULL;
  while (host_this != NULL)
  {
    host_next = host_this->next;

    csnmp_host_close_session (host_this);

    sfree (host_this->name);
    sfree (host_this->address);
    sfree (host_this->community);
    sfree (host_this->data_list);
    sfree (host_this);

    host_this = host_next;
  }

  data_this = data_head;
  data_head = NULL;
  while (data_this != NULL)
  {
    data_next = data_this->next;

    sfree (data_this->name);
    sfree (data_this->type);
    sfree (data_this->values);
    sfree (data_this);

    data_this = data_next;
  }

  return (0);
}