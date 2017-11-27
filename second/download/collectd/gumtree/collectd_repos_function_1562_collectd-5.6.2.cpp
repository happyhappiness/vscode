static int wrr_connect(struct riemann_host *host) /* {{{ */
{
  char const *node;
  int port;

  if (host->client)
    return 0;

  node = (host->node != NULL) ? host->node : RIEMANN_HOST;
  port = (host->port) ? host->port : RIEMANN_PORT;

  host->client = NULL;

  host->client = riemann_client_create(
      host->client_type, node, port, RIEMANN_CLIENT_OPTION_TLS_CA_FILE,
      host->tls_ca_file, RIEMANN_CLIENT_OPTION_TLS_CERT_FILE,
      host->tls_cert_file, RIEMANN_CLIENT_OPTION_TLS_KEY_FILE,
      host->tls_key_file, RIEMANN_CLIENT_OPTION_NONE);
  if (host->client == NULL) {
    c_complain(LOG_ERR, &host->init_complaint,
               "write_riemann plugin: Unable to connect to Riemann at %s:%d",
               node, port);
    return -1;
  }
#if RCC_VERSION_NUMBER >= 0x010800
  if (host->timeout.tv_sec != 0) {
    if (riemann_client_set_timeout(host->client, &host->timeout) != 0) {
      riemann_client_free(host->client);
      host->client = NULL;
      c_complain(LOG_ERR, &host->init_complaint,
                 "write_riemann plugin: Unable to connect to Riemann at %s:%d",
                 node, port);
      return -1;
    }
  }
#endif

  set_sock_opts(riemann_client_get_fd(host->client));

  c_release(LOG_INFO, &host->init_complaint,
            "write_riemann plugin: Successfully connected to %s:%d", node,
            port);

  return 0;
}