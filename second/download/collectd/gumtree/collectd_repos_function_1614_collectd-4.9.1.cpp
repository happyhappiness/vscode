static void cj_submit (cj_t *db, cj_key_t *key, value_t *value) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;
  char *host;

  vl.values     = value;
  vl.values_len = 1;

  if ((db->host == NULL)
      || (strcmp ("", db->host) == 0)
      || (strcmp (CJ_DEFAULT_HOST, db->host) == 0))
    host = hostname_g;
  else
    host = db->host;

  if (key->instance == NULL)
    ssnprintf (vl.type_instance, sizeof (vl.type_instance), "%s-%s",
               db->state[db->depth-1].name, db->state[db->depth].name);
  else
    sstrncpy (vl.type_instance, key->instance, sizeof (vl.type_instance));

  sstrncpy (vl.host, host, sizeof (vl.host));
  sstrncpy (vl.plugin, "curl_json", sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, db->instance, sizeof (vl.plugin_instance));
  sstrncpy (vl.type, key->type, sizeof (vl.type));

  plugin_dispatch_values (&vl);
}