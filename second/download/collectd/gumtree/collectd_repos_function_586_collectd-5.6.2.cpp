static int sensu_send_msg(struct sensu_host *host, const char *msg) /* {{{ */
{
  int status = 0;
  size_t buffer_len;

  status = sensu_connect(host);
  if (status != 0)
    return status;

  buffer_len = strlen(msg);

  status = (int)swrite(host->s, msg, buffer_len);
  sensu_close_socket(host);

  if (status != 0) {
    char errbuf[1024];
    ERROR("write_sensu plugin: Sending to Sensu at %s:%s failed: %s",
          (host->node != NULL) ? host->node : SENSU_HOST,
          (host->service != NULL) ? host->service : SENSU_PORT,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  return 0;
}