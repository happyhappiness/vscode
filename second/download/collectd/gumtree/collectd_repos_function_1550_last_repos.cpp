static struct MHD_Daemon *prom_start_daemon() {
  /* {{{ */
  struct MHD_Daemon *d = MHD_start_daemon(
      MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG, httpd_port,
      /* MHD_AcceptPolicyCallback = */ NULL,
      /* MHD_AcceptPolicyCallback arg = */ NULL, http_handler, NULL,
      MHD_OPTION_EXTERNAL_LOGGER, prom_logger, NULL, MHD_OPTION_END);
  if (d == NULL) {
    ERROR("write_prometheus plugin: MHD_start_daemon() failed.");
    return NULL;
  }

  return d;
}