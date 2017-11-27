static int cj_cb_double (void *ctx, double val)
{
  cj_t *db = (cj_t *)ctx;
  cj_key_t *key = db->state[db->depth].key;

  if (key != NULL)
  {
    value_t vt;
    int type;

    type = cj_get_type (key);
    if (type == DS_TYPE_COUNTER)
      vt.counter = (counter_t) val;
    else if (type == DS_TYPE_GAUGE)
      vt.gauge = (gauge_t) val;
    else if (type == DS_TYPE_DERIVE)
      vt.derive = (derive_t) val;
    else if (type == DS_TYPE_ABSOLUTE)
      vt.absolute = (absolute_t) val;
    else
      return 0;

    cj_submit (db, key, &vt);
  }
  return 1;
}