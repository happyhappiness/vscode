static int tss2_shutdown(void) {
  /*
   * Shutdown handler
   */
  vserver_list_t *entry;

  tss2_close_socket();

  entry = server_list;
  server_list = NULL;
  while (entry != NULL) {
    vserver_list_t *next;

    next = entry->next;
    sfree(entry);
    entry = next;
  }

  /* Get rid of the configuration */
  sfree(config_host);
  sfree(config_port);

  return (0);
}