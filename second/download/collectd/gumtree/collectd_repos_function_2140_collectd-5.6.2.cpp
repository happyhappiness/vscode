static int cj_cb_start_array(void *ctx) {
  cj_t *db = (cj_t *)ctx;
  cj_cb_inc_array_index(ctx, /* update_key = */ 1);
  if (db->depth + 1 < YAJL_MAX_DEPTH) {
    db->state[db->depth + 1].in_array = 1;
    db->state[db->depth + 1].index = 0;
  }
  return cj_cb_start(ctx);
}