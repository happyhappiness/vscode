static int za_read_gauge(kstat_t *ksp, const char *kstat_value,
                         const char *type, const char *type_instance) {
  long long tmp = get_zfs_value(ksp, (char *)kstat_value);
  if (tmp == -1LL) {
    WARNING("zfs_arc plugin: Reading kstat value \"%s\" failed.", kstat_value);
    return (-1);
  }

  za_submit(type, type_instance, &(value_t){.gauge = (gauge_t)tmp},
            /* values_num = */ 1);
  return (0);
}