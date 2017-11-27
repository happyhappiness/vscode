static int v5_mysql_qcache(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;

  if (vl->values_len != 5)
    return (FC_TARGET_STOP);

  /* Copy everything: Time, interval, host, ... */
  memcpy(&new_vl, vl, sizeof(new_vl));

  /* Reset data we can't simply copy */
  new_vl.values = &(value_t){.gauge = NAN};
  new_vl.values_len = 1;
  new_vl.meta = NULL;

  /* Change the type to "cache_result" */
  sstrncpy(new_vl.type, "cache_result", sizeof(new_vl.type));

  /* Dispatch new value lists instead of this one */
  new_vl.values[0].derive = (derive_t)vl->values[0].counter;
  sstrncpy(new_vl.type_instance, "qcache-hits", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  new_vl.values[0].derive = (derive_t)vl->values[1].counter;
  sstrncpy(new_vl.type_instance, "qcache-inserts",
           sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  new_vl.values[0].derive = (derive_t)vl->values[2].counter;
  sstrncpy(new_vl.type_instance, "qcache-not_cached",
           sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  new_vl.values[0].derive = (derive_t)vl->values[3].counter;
  sstrncpy(new_vl.type_instance, "qcache-prunes", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  /* The last data source is a gauge value, so we have to use a different type
   * here. */
  new_vl.values[0].gauge = vl->values[4].gauge;
  sstrncpy(new_vl.type, "cache_size", sizeof(new_vl.type));
  sstrncpy(new_vl.type_instance, "qcache", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  /* Abort processing */
  return (FC_TARGET_STOP);
}