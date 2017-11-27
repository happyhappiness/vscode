static int metric_family_update(Io__Prometheus__Client__MetricFamily *fam,
                                data_set_t const *ds, value_list_t const *vl,
                                size_t ds_index) {
  Io__Prometheus__Client__Metric *m = metric_family_get_metric(fam, vl);
  if (m == NULL)
    return -1;

  return metric_update(m, vl->values[ds_index], ds->ds[ds_index].type, vl->time,
                       vl->interval);
}