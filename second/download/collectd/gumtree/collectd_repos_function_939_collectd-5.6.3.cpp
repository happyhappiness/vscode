static int conn_read(void) {
  int size;
  int nconn;
  void *data;
  struct netinfo_header *header;
  struct netinfo_conn *conn;

  conn_reset_port_entry();

  size = netinfo(NETINFO_TCP, 0, 0, 0);
  if (size < 0) {
    ERROR("tcpconns plugin: netinfo failed return: %i", size);
    return (-1);
  }

  if (size == 0)
    return (0);

  if ((size - sizeof(struct netinfo_header)) % sizeof(struct netinfo_conn)) {
    ERROR("tcpconns plugin: invalid buffer size");
    return (-1);
  }

  data = malloc(size);
  if (data == NULL) {
    ERROR("tcpconns plugin: malloc failed");
    return (-1);
  }

  if (netinfo(NETINFO_TCP, data, &size, 0) < 0) {
    ERROR("tcpconns plugin: netinfo failed");
    free(data);
    return (-1);
  }

  header = (struct netinfo_header *)data;
  nconn = header->size;
  conn = (struct netinfo_conn *)(data + sizeof(struct netinfo_header));

  for (int i = 0; i < nconn; conn++, i++) {
    conn_handle_ports(conn->srcport, conn->dstport, conn->tcp_state);
  }

  free(data);

  conn_submit_all();

  return (0);
}