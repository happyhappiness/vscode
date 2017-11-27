static int ping_shutdown(void) /* {{{ */
{
  hostlist_t *hl;

  INFO("ping plugin: Shutting down thread.");
  if (stop_thread() < 0)
    return (-1);

  hl = hostlist_head;
  while (hl != NULL) {
    hostlist_t *hl_next;

    hl_next = hl->next;

    sfree(hl->host);
    sfree(hl);

    hl = hl_next;
  }

  if (ping_data != NULL) {
    free(ping_data);
    ping_data = NULL;
  }

  return (0);
}