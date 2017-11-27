static int tcsv_read_buffer(instance_definition_t *id, char *buffer,
                            size_t buffer_size) {
  char **metrics;
  size_t metrics_num;

  char *ptr;
  size_t i;

  /* Remove newlines at the end of line. */
  while (buffer_size > 0) {
    if ((buffer[buffer_size - 1] == '\n') ||
        (buffer[buffer_size - 1] == '\r')) {
      buffer[buffer_size - 1] = 0;
      buffer_size--;
    } else {
      break;
    }
  }

  /* Ignore empty lines. */
  if ((buffer_size == 0) || (buffer[0] == '#'))
    return (0);

  /* Count the number of fields. */
  metrics_num = 1;
  for (i = 0; i < buffer_size; i++) {
    if (buffer[i] == ',')
      metrics_num++;
  }

  if (metrics_num == 1) {
    ERROR("tail_csv plugin: last line of `%s' does not contain "
          "enough values.",
          id->path);
    return (-1);
  }

  /* Create a list of all values */
  metrics = calloc(metrics_num, sizeof(*metrics));
  if (metrics == NULL) {
    ERROR("tail_csv plugin: calloc failed.");
    return (ENOMEM);
  }

  ptr = buffer;
  metrics[0] = ptr;
  i = 1;
  for (ptr = buffer; *ptr != 0; ptr++) {
    if (*ptr != ',')
      continue;

    *ptr = 0;
    metrics[i] = ptr + 1;
    i++;
  }
  assert(i == metrics_num);

  /* Register values */
  for (i = 0; i < id->metric_list_len; ++i) {
    metric_definition_t *md = id->metric_list[i];

    if (!tcsv_check_index(md->value_from, metrics_num, md->name) ||
        !tcsv_check_index(id->time_from, metrics_num, md->name))
      continue;

    tcsv_read_metric(id, md, metrics, metrics_num);
  }

  /* Free up resources */
  sfree(metrics);
  return (0);
}