static int cj_cb_number (void *ctx,
    const char *number, yajl_len_t number_len)
{
  char buffer[number_len + 1];

  cj_t *db = (cj_t *)ctx;
  cj_key_t *key = db->state[db->depth].key;
  char *endptr;
  value_t vt;
  int type;

  if (key == NULL)
    return (CJ_CB_CONTINUE);

  memcpy (buffer, number, number_len);
  buffer[sizeof (buffer) - 1] = 0;

  type = cj_get_type (key);
  if (type < 0)
    return (CJ_CB_CONTINUE);

  endptr = NULL;
  errno = 0;

  if (type == DS_TYPE_COUNTER)
    vt.counter = (counter_t) strtoull (buffer, &endptr, /* base = */ 0);
  else if (type == DS_TYPE_GAUGE)
    vt.gauge = (gauge_t) strtod (buffer, &endptr);
  else if (type == DS_TYPE_DERIVE)
    vt.derive = (derive_t) strtoll (buffer, &endptr, /* base = */ 0);
  else if (type == DS_TYPE_ABSOLUTE)
    vt.absolute = (absolute_t) strtoull (buffer, &endptr, /* base = */ 0);
  else
  {
    ERROR ("curl_json plugin: Unknown data source type: \"%s\"", key->type);
    return (CJ_CB_ABORT);
  }

  if ((endptr == &buffer[0]) || (errno != 0))
  {
    NOTICE ("curl_json plugin: Overflow while parsing number. "
        "Ignoring this value.");
    return (CJ_CB_CONTINUE);
  }

  cj_submit (db, key, &vt);
  return (CJ_CB_CONTINUE);
}