static int conn_handle_ports (uint16_t port_local, uint16_t port_remote, uint8_t state)
{
  port_entry_t *pe = NULL;

  if ((state > TCP_STATE_MAX)
#if TCP_STATE_MIN > 0
      || (state < TCP_STATE_MIN)
#endif
     )
  {
    NOTICE ("tcpconns plugin: Ignoring connection with unknown state 0x%02x.",
	state);
    return (-1);
  }

  /* Listening sockets */
  if ((state == TCP_STATE_LISTEN) && (port_collect_listening != 0))
  {
    pe = conn_get_port_entry (port_local, 1 /* create */);
    if (pe != NULL)
      pe->flags |= PORT_IS_LISTENING;
  }

  DEBUG ("tcpconns plugin: Connection %hu <-> %hu (%s)",
      port_local, port_remote, tcp_state[state]);

  pe = conn_get_port_entry (port_local, 0 /* no create */);
  if (pe != NULL)
    pe->count_local[state]++;

  pe = conn_get_port_entry (port_remote, 0 /* no create */);
  if (pe != NULL)
    pe->count_remote[state]++;

  return (0);
}