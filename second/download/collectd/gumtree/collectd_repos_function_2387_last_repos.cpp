static int cj_cb_end(void *ctx) {
  cj_t *db = (cj_t *)ctx;
  memset(&db->state[db->depth], 0, sizeof(db->state[db->depth]));
  db->depth--;
  cj_advance_array(ctx);
  return CJ_CB_CONTINUE;
}