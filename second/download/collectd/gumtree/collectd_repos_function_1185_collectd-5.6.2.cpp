static int tss2_add_vserver(int vserver_port) {
  /*
   * Adds a new vserver to the linked list
   */
  vserver_list_t *entry;

  /* Check port range */
  if ((vserver_port <= 0) || (vserver_port > 65535)) {
    ERROR("teamspeak2 plugin: VServer port is invalid: %i", vserver_port);
    return (-1);
  }

  /* Allocate memory */
  entry = calloc(1, sizeof(*entry));
  if (entry == NULL) {
    ERROR("teamspeak2 plugin: calloc failed.");
    return (-1);
  }

  /* Save data */
  entry->port = vserver_port;

  /* Insert to list */
  if (server_list == NULL) {
    /* Add the server as the first element */
    server_list = entry;
  } else {
    vserver_list_t *prev;

    /* Add the server to the end of the list */
    prev = server_list;
    while (prev->next != NULL)
      prev = prev->next;
    prev->next = entry;
  }

  INFO("teamspeak2 plugin: Registered new vserver: %i", vserver_port);

  return (0);
}