static void submit_derive2 (const char *type, const char *type_inst,
    derive_t value0, derive_t value1, memcached_t *st)
{
  value_t values[2];
  value_list_t vl = VALUE_LIST_INIT;
  memcached_init_vl (&vl, st);

  values[0].derive = value0;
  values[1].derive = value1;

  vl.values = values;
  vl.values_len = 2;
  sstrncpy (vl.type, type, sizeof (vl.type));
  if (type_inst != NULL)
    sstrncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);
}