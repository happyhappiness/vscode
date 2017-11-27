static void metric_family_destroy(Io__Prometheus__Client__MetricFamily *msg) {
  if (msg == NULL)
    return;

  sfree(msg->name);
  sfree(msg->help);

  for (size_t i = 0; i < msg->n_metric; i++) {
    metric_destroy(msg->metric[i]);
  }
  sfree(msg->metric);

  sfree(msg);
}