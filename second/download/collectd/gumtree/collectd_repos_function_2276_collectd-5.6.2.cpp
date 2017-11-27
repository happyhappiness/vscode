lcc_server_t *lcc_server_create(lcc_network_t *net, /* {{{ */
                                const char *node, const char *service) {
  lcc_server_t *srv;

  if ((net == NULL) || (node == NULL))
    return (NULL);
  if (service == NULL)
    service = NET_DEFAULT_PORT;

  srv = calloc(1, sizeof(*srv));
  if (srv == NULL)
    return (NULL);

  srv->fd = -1;
  srv->security_level = NONE;
  srv->username = NULL;
  srv->password = NULL;
  srv->next = NULL;

  srv->node = strdup(node);
  if (srv->node == NULL) {
    free(srv);
    return (NULL);
  }

  srv->service = strdup(service);
  if (srv->service == NULL) {
    free(srv->node);
    free(srv);
    return (NULL);
  }

  srv->buffer = lcc_network_buffer_create(/* size = */ 0);
  if (srv->buffer == NULL) {
    free(srv->service);
    free(srv->node);
    free(srv);
    return (NULL);
  }

  if (net->servers == NULL) {
    net->servers = srv;
  } else {
    lcc_server_t *last = net->servers;

    while (last->next != NULL)
      last = last->next;

    last->next = srv;
  }

  return (srv);
}