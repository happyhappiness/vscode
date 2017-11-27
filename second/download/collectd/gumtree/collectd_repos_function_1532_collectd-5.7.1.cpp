static Io__Prometheus__Client__MetricFamily *
metric_family_create(char *name, data_set_t const *ds, value_list_t const *vl,
                     size_t ds_index) {
  Io__Prometheus__Client__MetricFamily *msg = calloc(1, sizeof(*msg));
  if (msg == NULL)
    return NULL;
  io__prometheus__client__metric_family__init(msg);

  msg->name = name;

  char help[1024];
  ssnprintf(
      help, sizeof(help),
      "write_prometheus plugin: '%s' Type: '%s', Dstype: '%s', Dsname: '%s'",
      vl->plugin, vl->type, DS_TYPE_TO_STRING(ds->ds[ds_index].type),
      ds->ds[ds_index].name);
  msg->help = strdup(help);

  msg->type = (ds->ds[ds_index].type == DS_TYPE_GAUGE)
                  ? IO__PROMETHEUS__CLIENT__METRIC_TYPE__GAUGE
                  : IO__PROMETHEUS__CLIENT__METRIC_TYPE__COUNTER;
  msg->has_type = 1;

  return msg;
}