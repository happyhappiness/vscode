static int wrr_send_nolock(struct riemann_host *host,
                           riemann_message_t *msg) /* {{{ */
{
  int status = 0;

  status = wrr_connect(host);
  if (status != 0) {
    return status;
  }

  status = riemann_client_send_message(host->client, msg);
  if (status != 0) {
    wrr_disconnect(host);
    return status;
  }

  /*
   * For TCP we need to receive message acknowledgemenent.
   */
  if (host->client_type != RIEMANN_CLIENT_UDP) {
    riemann_message_t *response;

    response = riemann_client_recv_message(host->client);

    if (response == NULL) {
      wrr_disconnect(host);
      return errno;
    }
    riemann_message_free(response);
  }

  return 0;
}