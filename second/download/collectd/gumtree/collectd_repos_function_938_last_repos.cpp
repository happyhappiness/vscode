static port_entry_t *conn_get_port_entry(uint16_t port, int create) {
  port_entry_t *ret;

  ret = port_list_head;
  while (ret != NULL) {
    if (ret->port == port)
      break;
    ret = ret->next;
  }

  if ((ret == NULL) && (create != 0)) {
    ret = calloc(1, sizeof(*ret));
    if (ret == NULL)
      return NULL;

    ret->port = port;
    ret->next = port_list_head;
    port_list_head = ret;
  }

  return ret;
}