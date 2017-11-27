static int udb_legacy_result_handle_result (udb_result_t *r, /* {{{ */
    udb_query_t *q, char **column_values)
{
  value_list_t vl = VALUE_LIST_INIT;
  value_t value;
  char *endptr;

  assert (r->legacy_mode == 1);
  assert (r->ds != NULL);
  assert (r->ds->ds_num == 1);

  vl.values = &value;
  vl.values_len = 1;

  endptr = NULL;
  errno = 0;
  if (r->ds->ds[0].type == DS_TYPE_COUNTER)
    vl.values[0].counter = (counter_t) strtoll (column_values[r->legacy_position],
        &endptr, /* base = */ 0);
  else if (r->ds->ds[0].type == DS_TYPE_GAUGE)
    vl.values[0].gauge = (gauge_t) strtod (column_values[r->legacy_position],
        &endptr);
  else
    errno = EINVAL;

  if ((endptr == column_values[r->legacy_position]) || (errno != 0))
  {
    WARNING ("db query utils: udb_result_submit: Parsing `%s' as %s failed.",
        column_values[r->legacy_position],
        (r->ds->ds[0].type == DS_TYPE_COUNTER) ? "counter" : "gauge");
    vl.values[0].gauge = NAN;
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