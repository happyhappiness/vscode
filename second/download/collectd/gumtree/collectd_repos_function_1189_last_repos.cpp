static void v5_swap_instances(value_list_t *vl) /* {{{ */
{
  char tmp[DATA_MAX_NAME_LEN];

  assert(sizeof(tmp) == sizeof(vl->plugin_instance));
  assert(sizeof(tmp) == sizeof(vl->type_instance));

  memcpy(tmp, vl->plugin_instance, sizeof(tmp));
  memcpy(vl->plugin_instance, vl->type_instance, sizeof(tmp));
  memcpy(vl->type_instance, tmp, sizeof(tmp));
}