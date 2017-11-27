static int cj_cb_number(void *ctx, const char *number, yajl_len_t number_len) {
  char buffer[number_len + 1];

  cj_t *db = (cj_t *)ctx;
  cj_key_t *key = db->state[db->depth].key;

  /* Create a null-terminated version of the string. */
  memcpy(buffer, number, number_len);
  buffer[sizeof(buffer) - 1] = 0;



  if (key == NULL) {
    /* no config for this element. */
    cj_advance_array(ctx);
    return CJ_CB_CONTINUE;
  } else if (!CJ_IS_KEY(key)) {
    /* the config expects a map or an array. */
    NOTICE(
        "curl_json plugin: Found \"%s\", but the configuration expects a map.",
        buffer);
    cj_advance_array(ctx);
    return CJ_CB_CONTINUE;
  }

  int type = cj_get_type(key);
  value_t vt;
  int status = parse_value(buffer, &vt, type);
  if (status != 0) {
    NOTICE("curl_json plugin: Unable to parse number: \"%s\"", buffer);
    cj_advance_array(ctx);
    return (CJ_CB_CONTINUE);
  }

  cj_submit(db, key, &vt);
  cj_advance_array(ctx);
  return (CJ_CB_CONTINUE);
}