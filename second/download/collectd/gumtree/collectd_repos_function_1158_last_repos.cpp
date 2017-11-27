static int cna_handle_system_data(const char *hostname, /* {{{ */
                                  cfg_system_t *cfg_system, na_elem_t *data,
                                  int interval) {
  na_elem_t *instances;
  na_elem_iter_t counter_iter;

  derive_t disk_read = 0, disk_written = 0;
  derive_t net_recv = 0, net_sent = 0;
  derive_t cpu_busy = 0, cpu_total = 0;
  uint32_t counter_flags = 0;

  const char *instance;
  cdtime_t timestamp;

  timestamp = cna_child_get_cdtime(data);

  instances = na_elem_child(na_elem_child(data, "instances"), "instance-data");
  if (instances == NULL) {
    ERROR("netapp plugin: cna_handle_system_data: "
          "na_elem_child (\"instances\") failed "
          "for host %s.",
          hostname);
    return -1;
  }

  instance = na_child_get_string(instances, "name");
  if (instance == NULL) {
    ERROR("netapp plugin: cna_handle_system_data: "
          "na_child_get_string (\"name\") failed "
          "for host %s.",
          hostname);
    return -1;
  }

  counter_iter = na_child_iterator(na_elem_child(instances, "counters"));
  for (na_elem_t *counter = na_iterator_next(&counter_iter); counter != NULL;
       counter = na_iterator_next(&counter_iter)) {
    const char *name;
    uint64_t value;

    name = na_child_get_string(counter, "name");
    if (name == NULL)
      continue;

    value = na_child_get_uint64(counter, "value", UINT64_MAX);
    if (value == UINT64_MAX)
      continue;

    if (!strcmp(name, "disk_data_read")) {
      disk_read = (derive_t)(value * 1024);
      counter_flags |= 0x01;
    } else if (!strcmp(name, "disk_data_written")) {
      disk_written = (derive_t)(value * 1024);
      counter_flags |= 0x02;
    } else if (!strcmp(name, "net_data_recv")) {
      net_recv = (derive_t)(value * 1024);
      counter_flags |= 0x04;
    } else if (!strcmp(name, "net_data_sent")) {
      net_sent = (derive_t)(value * 1024);
      counter_flags |= 0x08;
    } else if (!strcmp(name, "cpu_busy")) {
      cpu_busy = (derive_t)value;
      counter_flags |= 0x10;
    } else if (!strcmp(name, "cpu_elapsed_time")) {
      cpu_total = (derive_t)value;
      counter_flags |= 0x20;
    } else if ((cfg_system->flags & CFG_SYSTEM_OPS) && (value > 0) &&
               (strlen(name) > 4) &&
               (!strcmp(name + strlen(name) - 4, "_ops"))) {
      submit_derive(hostname, instance, "disk_ops_complex", name,
                    (derive_t)value, timestamp, interval);
    }
  } /* for (counter) */

  if ((cfg_system->flags & CFG_SYSTEM_DISK) &&
      (HAS_ALL_FLAGS(counter_flags, 0x01 | 0x02)))
    submit_two_derive(hostname, instance, "disk_octets", NULL, disk_read,
                      disk_written, timestamp, interval);

  if ((cfg_system->flags & CFG_SYSTEM_NET) &&
      (HAS_ALL_FLAGS(counter_flags, 0x04 | 0x08)))
    submit_two_derive(hostname, instance, "if_octets", NULL, net_recv, net_sent,
                      timestamp, interval);

  if ((cfg_system->flags & CFG_SYSTEM_CPU) &&
      (HAS_ALL_FLAGS(counter_flags, 0x10 | 0x20))) {
    submit_derive(hostname, instance, "cpu", "system", cpu_busy, timestamp,
                  interval);
    submit_derive(hostname, instance, "cpu", "idle", cpu_total - cpu_busy,
                  timestamp, interval);
  }

  return 0;
}