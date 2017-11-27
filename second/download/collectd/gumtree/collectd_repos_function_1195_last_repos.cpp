static int v5_zfs_arc_l2_bytes(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;

  if (vl->values_len != 2)
    return FC_TARGET_STOP;

  /* Copy everything: Time, interval, host, ... */
  memcpy(&new_vl, vl, sizeof(new_vl));

  /* Reset data we can't simply copy */
  new_vl.meta = NULL;

  /* Change the type/-instance to "io_octets-L2" */
  sstrncpy(new_vl.type, "io_octets", sizeof(new_vl.type));
  sstrncpy(new_vl.type_instance, "L2", sizeof(new_vl.type_instance));

  /* Copy the actual values. */
  value_t values[] = {
      {.derive = (derive_t)vl->values[0].counter},
      {.derive = (derive_t)vl->values[1].counter},
  };
  new_vl.values = values;
  new_vl.values_len = STATIC_ARRAY_SIZE(values);

  /* Dispatch new value lists instead of this one */
  plugin_dispatch_values(&new_vl);

  /* Abort processing */
  return FC_TARGET_STOP;
}