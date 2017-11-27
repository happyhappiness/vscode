static int prom_shutdown() {
  if (httpd != NULL) {
    MHD_stop_daemon(httpd);
    httpd = NULL;
  }

  pthread_mutex_lock(&metrics_lock);
  if (metrics != NULL) {
    char *name;
    Io__Prometheus__Client__MetricFamily *fam;
    while (c_avl_pick(metrics, (void *)&name, (void *)&fam) == 0) {
      assert(name == fam->name);
      name = NULL;

      metric_family_destroy(fam);
    }
    c_avl_destroy(metrics);
    metrics = NULL;
  }
  pthread_mutex_unlock(&metrics_lock);

  return 0;
}