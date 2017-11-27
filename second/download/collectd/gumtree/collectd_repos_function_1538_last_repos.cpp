static Io__Prometheus__Client__Metric *
metric_clone(Io__Prometheus__Client__Metric const *orig) {
  Io__Prometheus__Client__Metric *copy = calloc(1, sizeof(*copy));
  if (copy == NULL)
    return NULL;
  io__prometheus__client__metric__init(copy);

  copy->n_label = orig->n_label;
  copy->label = calloc(copy->n_label, sizeof(*copy->label));
  if (copy->label == NULL) {
    sfree(copy);
    return NULL;
  }

  for (size_t i = 0; i < copy->n_label; i++) {
    copy->label[i] = label_pair_clone(orig->label[i]);
    if (copy->label[i] == NULL) {
      metric_destroy(copy);
      return NULL;
    }
  }

  return copy;
}