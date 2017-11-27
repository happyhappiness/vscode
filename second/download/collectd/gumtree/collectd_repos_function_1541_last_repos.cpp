static int
metric_family_delete_metric(Io__Prometheus__Client__MetricFamily *fam,
                            value_list_t const *vl) {
  Io__Prometheus__Client__Metric *key = METRIC_INIT;
  METRIC_ADD_LABELS(key, vl);

  size_t i;
  for (i = 0; i < fam->n_metric; i++) {
    if (metric_cmp(&key, &fam->metric[i]) == 0)
      break;
  }

  if (i >= fam->n_metric)
    return ENOENT;

  metric_destroy(fam->metric[i]);
  if ((fam->n_metric - 1) > i)
    memmove(&fam->metric[i], &fam->metric[i + 1],
            ((fam->n_metric - 1) - i) * sizeof(fam->metric[i]));
  fam->n_metric--;

  if (fam->n_metric == 0) {
    sfree(fam->metric);
    return 0;
  }

  Io__Prometheus__Client__Metric **tmp =
      realloc(fam->metric, fam->n_metric * sizeof(*fam->metric));
  if (tmp != NULL)
    fam->metric = tmp;

  return 0;
}