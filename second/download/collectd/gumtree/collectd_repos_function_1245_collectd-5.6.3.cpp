static int tcsv_read_metric(instance_definition_t *id, metric_definition_t *md,
                            char **fields, size_t fields_num) {
  value_t v;
  cdtime_t t = 0;
  int status;

  if (md->data_source_type == -1)
    return (EINVAL);

  assert(md->value_from >= 0);
  if (((size_t)md->value_from) >= fields_num)
    return (EINVAL);

  status = parse_value(fields[md->value_from], &v, md->data_source_type);
  if (status != 0)
    return (status);

  if (id->time_from >= 0) {
    if (((size_t)id->time_from) >= fields_num)
      return (EINVAL);
    t = parse_time(fields[id->time_from]);
  }

  return (tcsv_submit(id, md, v, t));
}