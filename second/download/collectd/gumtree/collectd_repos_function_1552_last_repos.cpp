static int prom_init() {
  if (metrics == NULL) {
    metrics = c_avl_create((void *)strcmp);
    if (metrics == NULL) {
      ERROR("write_prometheus plugin: c_avl_create() failed.");
      return -1;
    }
  }

  if (httpd == NULL) {
    httpd = prom_start_daemon();
    if (httpd == NULL) {
      ERROR("write_prometheus plugin: MHD_start_daemon() failed.");
      return -1;
    }
    DEBUG("write_prometheus plugin: Successfully started microhttpd %s",
          MHD_get_version());
  }

  return 0;
}