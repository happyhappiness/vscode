static void int_server_destroy (lcc_server_t *srv) /* {{{ */
{
  lcc_server_t *next;

  if (srv == NULL)
    return;

  server_close_socket (srv);

  next = srv->next;

  free (srv->node);
  free (srv->service);
  free (srv->username);
  free (srv->password);
  free (srv);

  int_server_destroy (next);
}