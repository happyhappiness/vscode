static int server_value_add(lcc_server_t *srv, /* {{{ */
                            const lcc_value_list_t *vl) {
  int status;

  status = lcc_network_buffer_add_value(srv->buffer, vl);
  if (status == 0)
    return (0);

  server_send_buffer(srv);
  return (lcc_network_buffer_add_value(srv->buffer, vl));
}