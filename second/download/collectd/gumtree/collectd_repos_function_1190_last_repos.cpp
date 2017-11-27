static int v5_df(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  value_list_t new_vl;

  /* Can't upgrade if both instances have been set. */
  if ((vl->plugin_instance[0] != 0) && (vl->type_instance[0] != 0))
    return FC_TARGET_CONTINUE;

  /* Copy everything: Time, interval, host, ... */
  memcpy(&new_vl, vl, sizeof(new_vl));

  /* Reset data we can't simply copy */
  new_vl.values = &(value_t){.gauge = NAN};
  new_vl.values_len = 1;
  new_vl.meta = NULL;

  /* Move the mount point name to the plugin instance */
  if (new_vl.plugin_instance[0] == 0)
    v5_swap_instances(&new_vl);

  /* Change the type to "df_complex" */
  sstrncpy(new_vl.type, "df_complex", sizeof(new_vl.type));

  /* Dispatch two new value lists instead of this one */
  new_vl.values[0].gauge = vl->values[0].gauge;
  sstrncpy(new_vl.type_instance, "used", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  new_vl.values[0].gauge = vl->values[1].gauge;
  sstrncpy(new_vl.type_instance, "free", sizeof(new_vl.type_instance));
  plugin_dispatch_values(&new_vl);

  /* Abort processing */
  return FC_TARGET_STOP;
}