static int udb_legacy_result_handle_result (udb_result_t *r, /* {{{ */
    udb_query_t *q, char **column_values)
{
  value_list_t vl = VALUE_LIST_INIT;
  value_t value;
  char *value_str;

  assert (r->legacy_mode == 1);
  assert (r->ds != NULL);
  assert (r->ds->ds_num == 1);

  vl.values = &value;
  vl.values_len = 1;

  value_str = column_values[r->legacy_position];
  if (0 != parse_value (value_str, &vl.values[0], r->ds->ds[0]))
  {
    ERROR ("db query utils: udb_legacy_result_handle_result: "
        "Parsing `%s' as %s failed.", value_str,
        (r->ds->ds[0].type == DS_TYPE_COUNTER) ? "counter" : "gauge");
    errno = EINVAL;
    return (-1);
  }

  sstrncpy (vl.host, q->host, sizeof (vl.host));
  sstrncpy (vl.plugin, q->plugin, sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, q->db_name, sizeof (vl.type_instance));
  sstrncpy (vl.type, r->type, sizeof (vl.type));

  if (r->instance_prefix != NULL)
    sstrncpy (vl.type_instance, r->instance_prefix,
        sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);

  return (0);
}