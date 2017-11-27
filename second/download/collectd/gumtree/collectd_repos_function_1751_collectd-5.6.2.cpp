static int memory_read(void) /* {{{ */
{
  value_t v[1];
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = v;
  vl.values_len = STATIC_ARRAY_SIZE(v);
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "memory", sizeof(vl.plugin));
  sstrncpy(vl.type, "memory", sizeof(vl.type));
  vl.time = cdtime();

  return (memory_read_internal(&vl));
}