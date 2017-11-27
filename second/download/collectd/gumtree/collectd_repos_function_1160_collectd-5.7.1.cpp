static int cna_handle_volume_perf_data(const char *hostname, /* {{{ */
                                       cfg_volume_perf_t *cvp, na_elem_t *data,
                                       cdtime_t interval) {
  cdtime_t timestamp;
  na_elem_t *elem_instances;
  na_elem_iter_t iter_instances;

  timestamp = cna_child_get_cdtime(data);

  elem_instances = na_elem_child(data, "instances");
  if (elem_instances == NULL) {
    ERROR("netapp plugin: handle_volume_perf_data: "
          "na_elem_child (\"instances\") failed "
          "for host %s.",
          hostname);
    return (-1);
  }

  iter_instances = na_child_iterator(elem_instances);
  for (na_elem_t *elem_instance = na_iterator_next(&iter_instances);
       elem_instance != NULL;
       elem_instance = na_iterator_next(&iter_instances)) {
    const char *name;

    data_volume_perf_t perf_data = {0};
    data_volume_perf_t *v;

    na_elem_t *elem_counters;
    na_elem_iter_t iter_counters;

    perf_data.timestamp = timestamp;

    name = na_child_get_string(elem_instance, "name");
    if (name == NULL)
      continue;

    /* get_volume_perf may return NULL if this volume is to be ignored. */
    v = get_volume_perf(cvp, name);
    if (v == NULL)
      continue;

    elem_counters = na_elem_child(elem_instance, "counters");
    if (elem_counters == NULL)
      continue;

    iter_counters = na_child_iterator(elem_counters);
    for (na_elem_t *elem_counter = na_iterator_next(&iter_counters);
         elem_counter != NULL;
         elem_counter = na_iterator_next(&iter_counters)) {
      const char *name;
      uint64_t value;

      name = na_child_get_string(elem_counter, "name");
      if (name == NULL)
        continue;

      value = na_child_get_uint64(elem_counter, "value", UINT64_MAX);
      if (value == UINT64_MAX)
        continue;

      if (!strcmp(name, "read_data")) {
        perf_data.read_bytes = value;
        perf_data.flags |= HAVE_VOLUME_PERF_BYTES_READ;
      } else if (!strcmp(name, "write_data")) {
        perf_data.write_bytes = value;
        perf_data.flags |= HAVE_VOLUME_PERF_BYTES_WRITE;
      } else if (!strcmp(name, "read_ops")) {
        perf_data.read_ops = value;
        perf_data.flags |= HAVE_VOLUME_PERF_OPS_READ;
      } else if (!strcmp(name, "write_ops")) {
        perf_data.write_ops = value;
        perf_data.flags |= HAVE_VOLUME_PERF_OPS_WRITE;
      } else if (!strcmp(name, "read_latency")) {
        perf_data.read_latency = value;
        perf_data.flags |= HAVE_VOLUME_PERF_LATENCY_READ;
      } else if (!strcmp(name, "write_latency")) {
        perf_data.write_latency = value;
        perf_data.flags |= HAVE_VOLUME_PERF_LATENCY_WRITE;
      }
    } /* for (elem_counter) */

    submit_volume_perf_data(hostname, v, &perf_data, interval);
  } /* for (volume) */

  return (0);
}