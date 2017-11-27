static struct MHD_Daemon *prom_start_daemon() {
  /* {{{ */
  int fd = prom_open_socket(PF_INET6);
  if (fd == -1)
    fd = prom_open_socket(PF_INET);
  if (fd == -1) {
    ERROR("write_prometheus plugin: Opening a listening socket failed.");
    return NULL;
  }

  struct MHD_Daemon *d = MHD_start_daemon(
      MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG, httpd_port,
      /* MHD_AcceptPolicyCallback = */ NULL,
      /* MHD_AcceptPolicyCallback arg = */ NULL, http_handler, NULL,
      MHD_OPTION_LISTEN_SOCKET, fd, MHD_OPTION_EXTERNAL_LOGGER, prom_logger,
      NULL, MHD_OPTION_END);
  if (d == NULL) {
    ERROR("write_prometheus plugin: MHD_start_daemon() failed.");
    close(fd);
    return NULL;
  }

  return d;
}