static void cj_submit (cj_t *db, cj_key_t *key, value_t *value) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;

  vl.values     = value;
  vl.values_len = 1;

  if (key->instance == NULL)
  {
    int len = 0;
    for (int i = 0; i < db->depth; i++)
      len += ssnprintf(vl.type_instance+len, sizeof(vl.type_instance)-len,
                       i ? "-%s" : "%s", db->state[i+1].name);
  }
  else
    sstrncpy (vl.type_instance, key->instance, sizeof (vl.type_instance));

  sstrncpy (vl.host, cj_host (db), sizeof (vl.host));
  sstrncpy (vl.plugin, "curl_json", sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, db->instance, sizeof (vl.plugin_instance));
  sstrncpy (vl.type, key->type, sizeof (vl.type));

  if (db->interval > 0)
    vl.interval = db->interval;

  plugin_dispatch_values (&vl);
}