static int cj_cb_end_array(void *ctx) {
  cj_t *db = (cj_t *)ctx;
  db->state[db->depth].in_array = 0;
  return cj_cb_end(ctx);
}