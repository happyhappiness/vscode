static int cj_cb_start_map(void *ctx) {
  cj_t *db = (cj_t *)ctx;

  if ((db->depth + 1) >= YAJL_MAX_DEPTH) {
    ERROR("curl_json plugin: %s depth exceeds max, aborting.",
          db->url ? db->url : db->sock);
    return CJ_CB_ABORT;
  }
  db->depth++;
  return CJ_CB_CONTINUE;
}