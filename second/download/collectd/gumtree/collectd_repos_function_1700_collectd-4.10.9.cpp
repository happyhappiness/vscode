static int cj_get_type (cj_key_t *key)
{
  const data_set_t *ds;

  ds = plugin_get_ds (key->type);
  if (ds == NULL)
  {
    static char type[DATA_MAX_NAME_LEN] = "!!!invalid!!!";

    assert (key->type != NULL);
    if (strcmp (type, key->type) != 0)
    {
      ERROR ("curl_json plugin: Unable to look up DS type \"%s\".",
          key->type);
      sstrncpy (type, key->type, sizeof (type));
    }

    return -1;
  }
  else if (ds->ds_num > 1)
  {
    static c_complain_t complaint = C_COMPLAIN_INIT_STATIC;

    c_complain_once (LOG_WARNING, &complaint,
        "curl_json plugin: The type \"%s\" has more than one data source. "
        "This is currently not supported. I will return the type of the "
        "first data source, but this will likely lead to problems later on.",
        key->type);
  }

  return ds->ds[0].type;
}