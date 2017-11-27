static void format_text(ProtobufCBuffer *buffer) {
  pthread_mutex_lock(&metrics_lock);

  char *unused_name;
  Io__Prometheus__Client__MetricFamily *fam;
  c_avl_iterator_t *iter = c_avl_get_iterator(metrics);
  while (c_avl_iterator_next(iter, (void *)&unused_name, (void *)&fam) == 0) {
    char line[1024]; /* 4x DATA_MAX_NAME_LEN? */

    ssnprintf(line, sizeof(line), "# HELP %s %s\n", fam->name, fam->help);
    buffer->append(buffer, strlen(line), (uint8_t *)line);

    ssnprintf(line, sizeof(line), "# TYPE %s %s\n", fam->name,
              (fam->type == IO__PROMETHEUS__CLIENT__METRIC_TYPE__GAUGE)
                  ? "gauge"
                  : "counter");
    buffer->append(buffer, strlen(line), (uint8_t *)line);

    for (size_t i = 0; i < fam->n_metric; i++) {
      Io__Prometheus__Client__Metric *m = fam->metric[i];

      char labels[1024];

      char timestamp_ms[24] = "";
      if (m->has_timestamp_ms)
        ssnprintf(timestamp_ms, sizeof(timestamp_ms), " %" PRIi64,
                  m->timestamp_ms);

      if (fam->type == IO__PROMETHEUS__CLIENT__METRIC_TYPE__GAUGE)
        ssnprintf(line, sizeof(line), "%s{%s} " GAUGE_FORMAT "%s\n", fam->name,
                  format_labels(labels, sizeof(labels), m), m->gauge->value,
                  timestamp_ms);
      else /* if (fam->type == IO__PROMETHEUS__CLIENT__METRIC_TYPE__COUNTER) */
        ssnprintf(line, sizeof(line), "%s{%s} %.0f%s\n", fam->name,
                  format_labels(labels, sizeof(labels), m), m->counter->value,
                  timestamp_ms);

      buffer->append(buffer, strlen(line), (uint8_t *)line);
    }
  }
  c_avl_iterator_destroy(iter);

  char server[1024];
  ssnprintf(server, sizeof(server), "\n# collectd/write_prometheus %s at %s\n",
            PACKAGE_VERSION, hostname_g);
  buffer->append(buffer, strlen(server), (uint8_t *)server);

  pthread_mutex_unlock(&metrics_lock);
}