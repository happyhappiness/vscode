static int v5_zfs_arc_counts (const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;
  value_t new_value;
  _Bool is_hits;

  if (vl->values_len != 4)
    return (FC_TARGET_STOP);

  if (strcmp ("hits", vl->type_instance) == 0)
    is_hits = 1;
  else if (strcmp ("misses", vl->type_instance) == 0)
    is_hits = 0;
  else
    return (FC_TARGET_STOP);

  /* Copy everything: Time, interval, host, ... */
  memcpy (&new_vl, vl, sizeof (new_vl));

  /* Reset data we can't simply copy */
  new_vl.values = &new_value;
  new_vl.values_len = 1;
  new_vl.meta = NULL;

  /* Change the type to "cache_result" */
  sstrncpy (new_vl.type, "cache_result", sizeof (new_vl.type));

  /* Dispatch new value lists instead of this one */
  new_vl.values[0].derive = (derive_t) vl->values[0].counter;
  ssnprintf (new_vl.type_instance, sizeof (new_vl.type_instance),
      "demand_data-%s",
      is_hits ? "hit" : "miss");
  plugin_dispatch_values (&new_vl);

  new_vl.values[0].derive = (derive_t) vl->values[1].counter;
  ssnprintf (new_vl.type_instance, sizeof (new_vl.type_instance),
      "demand_metadata-%s",
      is_hits ? "hit" : "miss");
  plugin_dispatch_values (&new_vl);

  new_vl.values[0].derive = (derive_t) vl->values[2].counter;
  ssnprintf (new_vl.type_instance, sizeof (new_vl.type_instance),
      "prefetch_data-%s",
      is_hits ? "hit" : "miss");
  plugin_dispatch_values (&new_vl);

  new_vl.values[0].derive = (derive_t) vl->values[3].counter;
  ssnprintf (new_vl.type_instance, sizeof (new_vl.type_instance),
      "prefetch_metadata-%s",
      is_hits ? "hit" : "miss");
  plugin_dispatch_values (&new_vl);

  /* Abort processing */
  return (FC_TARGET_STOP);
}