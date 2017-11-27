static bson *wm_create_bson (const data_set_t *ds, /* {{{ */
    const value_list_t *vl,
    _Bool store_rates)
{
  bson *ret;
  gauge_t *rates;

  ret = bson_alloc (); /* matched by bson_dealloc() */
  if (ret == NULL)
  {
    ERROR ("write_mongodb plugin: bson_create failed.");
    return (NULL);
  }

  if (store_rates)
  {
    rates = uc_get_rate (ds, vl);
    if (rates == NULL)
    {
      ERROR ("write_mongodb plugin: uc_get_rate() failed.");
      return (NULL);
    }
  }
  else
  {
    rates = NULL;
  }

  bson_init (ret); /* matched by bson_destroy() */
  bson_append_date (ret, "time", (bson_date_t) CDTIME_T_TO_MS (vl->time));
  bson_append_string (ret, "host", vl->host);
  bson_append_string (ret, "plugin", vl->plugin);
  bson_append_string (ret, "plugin_instance", vl->plugin_instance);
  bson_append_string (ret, "type", vl->type);
  bson_append_string (ret, "type_instance", vl->type_instance);

  bson_append_start_array (ret, "values"); /* {{{ */
  for (int i = 0; i < ds->ds_num; i++)
  {
    char key[16];

    ssnprintf (key, sizeof (key), "%i", i);

    if (ds->ds[i].type == DS_TYPE_GAUGE)
      bson_append_double(ret, key, vl->values[i].gauge);
    else if (store_rates)
      bson_append_double(ret, key, (double) rates[i]);
    else if (ds->ds[i].type == DS_TYPE_COUNTER)
      bson_append_long(ret, key, vl->values[i].counter);
    else if (ds->ds[i].type == DS_TYPE_DERIVE)
      bson_append_long(ret, key, vl->values[i].derive);
    else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
      bson_append_long(ret, key, vl->values[i].absolute);
    else
      assert (23 == 42);
  }
  bson_append_finish_array (ret); /* }}} values */

  bson_append_start_array (ret, "dstypes"); /* {{{ */
  for (int i = 0; i < ds->ds_num; i++)
  {
    char key[16];

    ssnprintf (key, sizeof (key), "%i", i);

    if (store_rates)
      bson_append_string (ret, key, "gauge");
    else
      bson_append_string (ret, key, DS_TYPE_TO_STRING (ds->ds[i].type));
  }
  bson_append_finish_array (ret); /* }}} dstypes */

  bson_append_start_array (ret, "dsnames"); /* {{{ */
  for (int i = 0; i < ds->ds_num; i++)
  {
    char key[16];

    ssnprintf (key, sizeof (key), "%i", i);
    bson_append_string (ret, key, ds->ds[i].name);
  }
  bson_append_finish_array (ret); /* }}} dsnames */

  bson_finish (ret);

  sfree (rates);
  return (ret);
}