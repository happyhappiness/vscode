static int v5_zfs_arc_ratio(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;

  if (vl->values_len != 1)
    return (FC_TARGET_STOP);

  /* Copy everything: Time, interval, host, ... */
  memcpy(&new_vl, vl, sizeof(new_vl));

  /* Reset data we can't simply copy */
  new_vl.values = &(value_t){.gauge = NAN};
  new_vl.values_len = 1;
  new_vl.meta = NULL;

  new_vl.values[0].gauge = (gauge_t)vl->values[0].gauge;

  /* Change the type to "cache_ratio" */
  sstrncpy(new_vl.type, "cache_ratio", sizeof(new_vl.type));

  /* Adapt the type instance */
  if (strcmp("L1", vl->type_instance) == 0)
    sstrncpy(new_vl.type_instance, "arc", sizeof(new_vl.type_instance));

  /* Dispatch new value lists instead of this one */
  plugin_dispatch_values(&new_vl);

  /* Abort processing */
  return (FC_TARGET_STOP);
}