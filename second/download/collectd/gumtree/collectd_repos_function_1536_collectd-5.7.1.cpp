static int prom_init() {
  if (metrics == NULL) {
    metrics = c_avl_create((void *)strcmp);
    if (metrics == NULL) {
      ERROR("write_prometheus plugin: c_avl_create() failed.");
      return -1;
    }
  }

  if (httpd == NULL) {
    unsigned int flags = MHD_USE_THREAD_PER_CONNECTION;
#if MHD_VERSION >= 0x00093300
    flags |= MHD_USE_DUAL_STACK;
#endif

    httpd = MHD_start_daemon(flags, httpd_port,
                             /* MHD_AcceptPolicyCallback = */ NULL,
                             /* MHD_AcceptPolicyCallback arg = */ NULL,
                             http_handler, NULL, MHD_OPTION_END);
    if (httpd == NULL) {
      ERROR("write_prometheus plugin: MHD_start_daemon() failed.");
      return -1;
    }
    DEBUG("write_prometheus plugin: Successfully started microhttpd %s",
          MHD_get_version());
  }

  return 0;
}