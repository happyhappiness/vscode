static int cj_cb_string (void *ctx, const unsigned char *val,
    yajl_len_t len)
{
  cj_t *db = (cj_t *)ctx;
  char str[len + 1];

  /* Create a null-terminated version of the string. */
  memcpy (str, val, len);
  str[len] = 0;

  /* No configuration for this string -> simply return. */
  if (db->state[db->depth].key == NULL)
    return (CJ_CB_CONTINUE);

  if (!CJ_IS_KEY (db->state[db->depth].key))
  {
    NOTICE ("curl_json plugin: Found string \"%s\", but the configuration "
        "expects a map here.", str);
    return (CJ_CB_CONTINUE);
  }

  /* Handle the string as if it was a number. */
  return (cj_cb_number (ctx, (const char *) val, len));
}