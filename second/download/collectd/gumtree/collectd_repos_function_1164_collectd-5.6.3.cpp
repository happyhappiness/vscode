static int v5_zfs_arc_size(const data_set_t *ds, value_list_t *vl) /* {{{ */
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

  /* Change the type to "cache_size" */
  sstrncpy(new_vl.type, "cache_size", sizeof(new_vl.type));

  /* Dispatch new value lists instead of this one */
  new_vl.values[0].derive = (derive_t)vl->values[0].counter;
  sstrncpy(new_vl.type_instance, "arc", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  /* Abort processing */
  return (FC_TARGET_STOP);
}