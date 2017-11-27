static int v5_interface(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  if ((vl->plugin_instance[0] != 0) || (vl->type_instance[0] == 0))
    return (FC_TARGET_CONTINUE);

  v5_swap_instances(vl);
  return (FC_TARGET_CONTINUE);
}