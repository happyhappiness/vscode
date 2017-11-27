static int za_read_gauge (kstat_t *ksp, const char *kstat_value,
    const char *type, const char *type_instance)
{
  long long tmp;
  value_t v;

  tmp = get_kstat_value (ksp, kstat_value);
  if (tmp == -1LL)
  {
    ERROR ("zfs_arc plugin: Reading kstat value \"%s\" failed.", kstat_value);
    return (-1);
  }

  v.gauge = (gauge_t) tmp;
  za_submit (type, type_instance, /* values = */ &v, /* values_num = */ 1);
}