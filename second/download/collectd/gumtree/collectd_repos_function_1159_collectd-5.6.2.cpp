static int v5_mysql_threads(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;
  value_t new_value;

  if (vl->values_len != 4)
    return (FC_TARGET_STOP);

  /* Copy everything: Time, interval, host, ... */
  memcpy(&new_vl, vl, sizeof(new_vl));

  /* Reset data we can't simply copy */
  new_vl.values = &new_value;
  new_vl.values_len = 1;
  new_vl.meta = NULL;

  /* Change the type to "threads" */
  sstrncpy(new_vl.type, "threads", sizeof(new_vl.type));

  /* Dispatch new value lists instead of this one */
  new_vl.values[0].gauge = vl->values[0].gauge;
  sstrncpy(new_vl.type_instance, "running", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  new_vl.values[0].gauge = vl->values[1].gauge;
  sstrncpy(new_vl.type_instance, "connected", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  new_vl.values[0].gauge = vl->values[2].gauge;
  sstrncpy(new_vl.type_instance, "cached", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  /* The last data source is a counter value, so we have to use a different
   * type here. */
  new_vl.values[0].derive = (derive_t)vl->values[3].counter;
  sstrncpy(new_vl.type, "total_threads", sizeof(new_vl.type));
  sstrncpy(new_vl.type_instance, "created", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  /* Abort processing */
  return (FC_TARGET_STOP);
}