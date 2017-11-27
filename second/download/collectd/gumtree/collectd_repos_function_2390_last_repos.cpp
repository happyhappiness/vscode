static int cj_cb_start_array(void *ctx) {
  cj_t *db = (cj_t *)ctx;

  if ((db->depth + 1) >= YAJL_MAX_DEPTH) {
    ERROR("curl_json plugin: %s depth exceeds max, aborting.",
          db->url ? db->url : db->sock);
    return CJ_CB_ABORT;
  }
  db->depth++;
  db->state[db->depth].in_array = 1;
  db->state[db->depth].index = 0;

  cj_load_key(db, "0");

  return CJ_CB_CONTINUE;
}