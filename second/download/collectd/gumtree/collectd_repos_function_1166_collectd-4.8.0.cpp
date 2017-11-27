static int udb_result_submit (udb_result_t *r, udb_query_t *q) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;
  size_t i;

  assert (r != NULL);
  assert (r->legacy_mode == 0);
  assert (r->ds != NULL);
  assert (((size_t) r->ds->ds_num) == r->values_num);

  vl.values = (value_t *) calloc (r->ds->ds_num, sizeof (value_t));
  if (vl.values == NULL)
  {
    ERROR ("db query utils: malloc failed.");
    return (-1);
  }
  vl.values_len = r->ds->ds_num;

  for (i = 0; i < r->values_num; i++)
  {
    char *value_str = r->values_buffer[i];

    if (0 != parse_value (value_str, &vl.values[i], r->ds->ds[i].type))
    {
      ERROR ("db query utils: udb_result_submit: Parsing `%s' as %s failed.",
          value_str, DS_TYPE_TO_STRING (r->ds->ds[i].type));
      errno = EINVAL;
      return (-1);
    }
  }

  sstrncpy (vl.host, q->host, sizeof (vl.host));
  sstrncpy (vl.plugin, q->plugin, sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, q->db_name, sizeof (vl.type_instance));
  sstrncpy (vl.type, r->type, sizeof (vl.type));

  /* Set vl.type_instance {{{ */
  if (r->instances_num <= 0)
  {
    if (r->instance_prefix == NULL)
      vl.type_instance[0] = 0;
    else
      sstrncpy (vl.type_instance, r->instance_prefix,
          sizeof (vl.type_instance));
  }
  else /* if ((r->instances_num > 0) */
  {
    if (r->instance_prefix == NULL)
    {
      strjoin (vl.type_instance, sizeof (vl.type_instance),
          r->instances_buffer, r->instances_num, "-");
    }
    else
    {
      char tmp[DATA_MAX_NAME_LEN];

      strjoin (tmp, sizeof (tmp), r->instances_buffer, r->instances_num, "-");
      tmp[sizeof (tmp) - 1] = 0;

      snprintf (vl.type_instance, sizeof (vl.type_instance), "%s-%s",
          r->instance_prefix, tmp);
    }
  }
  vl.type_instance[sizeof (vl.type_instance) - 1] = 0;
  /* }}} */

  plugin_dispatch_values (&vl);

  sfree (vl.values);
  return (0);
}