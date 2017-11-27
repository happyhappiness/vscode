static int udb_legacy_result_handle_result (udb_result_t *r, /* {{{ */
    udb_query_preparation_area_t *q_area,
    udb_result_preparation_area_t *r_area,
    const udb_query_t const *q, char **column_values)
{
  value_list_t vl = VALUE_LIST_INIT;
  value_t value;
  char *value_str;

  assert (r->legacy_mode == 1);
  assert (r_area->ds != NULL);
  assert (r_area->ds->ds_num == 1);

  vl.values = &value;
  vl.values_len = 1;

  value_str = column_values[r->legacy_position];
  if (0 != parse_value (value_str, &vl.values[0], r_area->ds->ds[0].type))
  {
    ERROR ("db query utils: udb_legacy_result_handle_result: "
        "Parsing `%s' as %s failed.", value_str,
        DS_TYPE_TO_STRING (r_area->ds->ds[0].type));
    errno = EINVAL;
    return (-1);
  }

  if (q_area->interval > 0)
    vl.interval = q_area->interval;

  sstrncpy (vl.host, q_area->host, sizeof (vl.host));
  sstrncpy (vl.plugin, q_area->plugin, sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, q_area->db_name, sizeof (vl.type_instance));
  sstrncpy (vl.type, r->type, sizeof (vl.type));

  if (r->instance_prefix != NULL)
    sstrncpy (vl.type_instance, r->instance_prefix,
        sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);

  return (0);
}