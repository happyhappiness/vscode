static int udb_result_submit (udb_result_t *r, /* {{{ */
    udb_result_preparation_area_t *r_area,
    udb_query_t const *q, udb_query_preparation_area_t *q_area)
{
  value_list_t vl = VALUE_LIST_INIT;
  size_t i;
  int status;

  assert (r != NULL);
  assert (r_area->ds != NULL);
  assert (((size_t) r_area->ds->ds_num) == r->values_num);
  assert (r->values_num > 0);

  vl.values = (value_t *) calloc (r->values_num, sizeof (value_t));
  if (vl.values == NULL)
  {
    ERROR ("db query utils: malloc failed.");
    return (-1);
  }
  vl.values_len = r_area->ds->ds_num;

  for (i = 0; i < r->values_num; i++)
  {
    char *value_str = r_area->values_buffer[i];

    if (0 != parse_value (value_str, &vl.values[i], r_area->ds->ds[i].type))
    {
      ERROR ("db query utils: udb_result_submit: Parsing `%s' as %s failed.",
          value_str, DS_TYPE_TO_STRING (r_area->ds->ds[i].type));
      errno = EINVAL;
      return (-1);
    }
  }

  if (q_area->interval > 0)
    vl.interval = q_area->interval;

  sstrncpy (vl.host, q_area->host, sizeof (vl.host));
  sstrncpy (vl.plugin, q_area->plugin, sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, q_area->db_name, sizeof (vl.plugin_instance));
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
      int status = strjoin (vl.type_instance, sizeof (vl.type_instance),
          r_area->instances_buffer, r->instances_num, "-");
      if (status < 0)
      {
        ERROR ("udb_result_submit: creating type_instance failed with status %d.",
            status);
        return (status);
      }
    }
    else
    {
      char tmp[DATA_MAX_NAME_LEN];

      int status = strjoin (tmp, sizeof (tmp), r_area->instances_buffer,
          r->instances_num, "-");
      if (status < 0)
      {
        ERROR ("udb_result_submit: creating type_instance failed with status %d.",
            status);
        return (status);
      }
      tmp[sizeof (tmp) - 1] = 0;

      snprintf (vl.type_instance, sizeof (vl.type_instance), "%s-%s",
          r->instance_prefix, tmp);
    }
  }
  vl.type_instance[sizeof (vl.type_instance) - 1] = 0;
  /* }}} */

  /* Annotate meta data. {{{ */
  if (r->metadata_num > 0)
  {
    vl.meta = meta_data_create ();
    if (vl.meta == NULL)
    {
      ERROR ("db query utils:: meta_data_create failed.");
      return (-ENOMEM);
    }

    for (i = 0; i < r->metadata_num; i++)
    {
      status = meta_data_add_string (vl.meta, r->metadata[i],
          r_area->metadata_buffer[i]);
      if (status != 0)
      {
        ERROR ("db query utils:: meta_data_add_string failed.");
        meta_data_destroy (vl.meta);
        vl.meta = NULL;
        return (status);
      }
    }
  }
  /* }}} */

  plugin_dispatch_values (&vl);

  if (r->metadata_num > 0)
  {
    meta_data_destroy (vl.meta);
    vl.meta = NULL;
  }
  sfree (vl.values);
  return (0);
}