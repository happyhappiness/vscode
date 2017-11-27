static void metric_destroy(Io__Prometheus__Client__Metric *msg) {
  if (msg == NULL)
    return;

  for (size_t i = 0; i < msg->n_label; i++) {
    label_pair_destroy(msg->label[i]);
  }
  sfree(msg->label);

  sfree(msg->gauge);
  sfree(msg->counter);

  sfree(msg);
}