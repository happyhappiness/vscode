static void udb_result_submit (udb_result_t *r, udb_query_t *q) /* {{{ */
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
    return;
  }
  vl.values_len = r->ds->ds_num;

  for (i = 0; i < r->values_num; i++)
  {
    char *endptr;

    endptr = NULL;
    errno = 0;
    if (r->ds->ds[i].type == DS_TYPE_COUNTER)
      vl.values[i].counter = (counter_t) strtoll (r->values_buffer[i],
          &endptr, /* base = */ 0);
    else if (r->ds->ds[i].type == DS_TYPE_GAUGE)
      vl.values[i].gauge = (gauge_t) strtod (r->values_buffer[i], &endptr);
    else
      errno = EINVAL;

    if ((endptr == r->values_buffer[i]) || (errno != 0))
    {
      WARNING ("db query utils: udb_result_submit: Parsing `%s' as %s failed.",
          r->values_buffer[i],
          (r->ds->ds[i].type == DS_TYPE_COUNTER) ? "counter" : "gauge");
      vl.values[i].gauge = NAN;
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
}