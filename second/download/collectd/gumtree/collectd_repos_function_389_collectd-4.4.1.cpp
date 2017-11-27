static port_entry_t *conn_get_port_entry (uint16_t port, int create)
{
  port_entry_t *ret;

  ret = port_list_head;
  while (ret != NULL)
  {
    if (ret->port == port)
      break;
    ret = ret->next;
  }

  if ((ret == NULL) && (create != 0))
  {
    ret = (port_entry_t *) malloc (sizeof (port_entry_t));
    if (ret == NULL)
      return (NULL);
    memset (ret, '\0', sizeof (port_entry_t));

    ret->port = port;
    ret->next = port_list_head;
    port_list_head = ret;
  }

  return (ret);
}