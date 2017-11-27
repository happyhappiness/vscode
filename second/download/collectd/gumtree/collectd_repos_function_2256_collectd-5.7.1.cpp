static int cj_cb_number(void *ctx, const char *number, yajl_len_t number_len) {
  char buffer[number_len + 1];

  cj_t *db = (cj_t *)ctx;
  cj_key_t *key = db->state[db->depth].key;
  value_t vt;
  int type;
  int status;

  /* Create a null-terminated version of the string. */
  memcpy(buffer, number, number_len);
  buffer[sizeof(buffer) - 1] = 0;

  if ((key == NULL) || !CJ_IS_KEY(key)) {
    if (key != NULL &&
        !db->state[db->depth].in_array /*can be inhomogeneous*/) {
      NOTICE("curl_json plugin: Found \"%s\", but the configuration expects"
             " a map.",
             buffer);
      return (CJ_CB_CONTINUE);
    }

    cj_cb_inc_array_index(ctx, /* update_key = */ 1);
    key = db->state[db->depth].key;
    if ((key == NULL) || !CJ_IS_KEY(key)) {
      return (CJ_CB_CONTINUE);
    }
  } else {
    cj_cb_inc_array_index(ctx, /* update_key = */ 1);
  }

  type = cj_get_type(key);
  status = parse_value(buffer, &vt, type);
  if (status != 0) {
    NOTICE("curl_json plugin: Unable to parse number: \"%s\"", buffer);
    return (CJ_CB_CONTINUE);
  }

  cj_submit(db, key, &vt);
  return (CJ_CB_CONTINUE);
}