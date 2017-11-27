static int za_read_derive (kstat_t *ksp, const char *kstat_value,
    const char *type, const char *type_instance)
{
  long long tmp;
  value_t v;

  tmp = get_zfs_value (ksp, (char *)kstat_value);
  if (tmp == -1LL)
  {
    WARNING ("zfs_arc plugin: Reading kstat value \"%s\" failed.", kstat_value);
    return (-1);
  }

  v.derive = (derive_t) tmp;
  za_submit (type, type_instance, /* values = */ &v, /* values_num = */ 1);
  return (0);
}