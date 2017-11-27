static int simple_submit_match (cu_match_t *match, void *user_data)
{
  cu_tail_match_simple_t *data = (cu_tail_match_simple_t *) user_data;
  cu_match_value_t *match_value;
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[1];

  match_value = (cu_match_value_t *) match_get_user_data (match);
  if (match_value == NULL)
    return (-1);

  if ((match_value->ds_type & UTILS_MATCH_DS_TYPE_GAUGE)
      && (match_value->values_num == 0))
    values[0].gauge = NAN;
  else
    values[0] = match_value->value;

  vl.values = values;
  vl.values_len = 1;
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, data->plugin, sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, data->plugin_instance,
      sizeof (vl.plugin_instance));
  sstrncpy (vl.type, data->type, sizeof (vl.type));
  sstrncpy (vl.type_instance, data->type_instance,
      sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);

  if (match_value->ds_type & UTILS_MATCH_DS_TYPE_GAUGE)
  {
    match_value->value.gauge = NAN;
    match_value->values_num = 0;
  }

  return (0);
}