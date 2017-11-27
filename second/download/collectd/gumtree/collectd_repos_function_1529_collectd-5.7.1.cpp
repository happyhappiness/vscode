static Io__Prometheus__Client__Metric *
metric_family_get_metric(Io__Prometheus__Client__MetricFamily *fam,
                         value_list_t const *vl) {
  Io__Prometheus__Client__Metric *key = METRIC_INIT;
  METRIC_ADD_LABELS(key, vl);

  /* Metrics are sorted in metric_family_add_metric() so that we can do a binary
   * search here. */
  Io__Prometheus__Client__Metric **m = bsearch(
      &key, fam->metric, fam->n_metric, sizeof(*fam->metric), metric_cmp);

  if (m != NULL) {
    return *m;
  }

  Io__Prometheus__Client__Metric *new_metric = metric_clone(key);
  if (new_metric == NULL)
    return NULL;

  DEBUG("write_prometheus plugin: created new metric in family");
  int status = metric_family_add_metric(fam, new_metric);
  if (status != 0) {
    metric_destroy(new_metric);
    return NULL;
  }

  return new_metric;
}