static int v5_zfs_arc_l2_size (const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;
  value_t new_value;

  if (vl->values_len != 1)
    return (FC_TARGET_STOP);

  /* Copy everything: Time, interval, host, ... */
  memcpy (&new_vl, vl, sizeof (new_vl));

  /* Reset data we can't simply copy */
  new_vl.values = &new_value;
  new_vl.values_len = 1;
  new_vl.meta = NULL;

  new_vl.values[0].gauge = (gauge_t) vl->values[0].gauge;

  /* Change the type to "cache_size" */
  sstrncpy (new_vl.type, "cache_size", sizeof (new_vl.type));

  /* Adapt the type instance */
  sstrncpy (new_vl.type_instance, "L2", sizeof (new_vl.type_instance));

  /* Dispatch new value lists instead of this one */
  plugin_dispatch_values (&new_vl);

  /* Abort processing */
  return (FC_TARGET_STOP);
}