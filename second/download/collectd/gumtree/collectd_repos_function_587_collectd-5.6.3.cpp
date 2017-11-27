static int sensu_send(struct sensu_host *host, char const *msg) /* {{{ */
{
  int status = 0;

  status = sensu_send_msg(host, msg);
  if (status != 0) {
    host->flags &= ~F_READY;
    if (host->res != NULL) {
      freeaddrinfo(host->res);
      host->res = NULL;
    }
    return status;
  }

  return 0;
}