static int metric_family_add_metric(Io__Prometheus__Client__MetricFamily *fam,
                                    Io__Prometheus__Client__Metric *m) {
  Io__Prometheus__Client__Metric **tmp =
      realloc(fam->metric, (fam->n_metric + 1) * sizeof(*fam->metric));
  if (tmp == NULL)
    return ENOMEM;
  fam->metric = tmp;

  fam->metric[fam->n_metric] = m;
  fam->n_metric++;

  /* Sort the metrics so that lookup is fast. */
  qsort(fam->metric, fam->n_metric, sizeof(*fam->metric), metric_cmp);

  return 0;
}