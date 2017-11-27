static void conn_reset_port_entry (void)
{
  port_entry_t *prev = NULL;
  port_entry_t *pe = port_list_head;

  memset (&count_total, '\0', sizeof(count_total));

  while (pe != NULL)
  {
    /* If this entry was created while reading the files (ant not when handling
     * the configuration) remove it now. */
    if ((pe->flags & (PORT_COLLECT_LOCAL
            | PORT_COLLECT_REMOTE
            | PORT_IS_LISTENING)) == 0)
    {
      port_entry_t *next = pe->next;

      DEBUG ("tcpconns plugin: Removing temporary entry "
          "for listening port %"PRIu16, pe->port);

      if (prev == NULL)
        port_list_head = next;
      else
        prev->next = next;

      sfree (pe);
      pe = next;

      continue;
    }

    memset (pe->count_local, '\0', sizeof (pe->count_local));
    memset (pe->count_remote, '\0', sizeof (pe->count_remote));
    pe->flags &= ~PORT_IS_LISTENING;

    prev = pe;
    pe = pe->next;
  }
}