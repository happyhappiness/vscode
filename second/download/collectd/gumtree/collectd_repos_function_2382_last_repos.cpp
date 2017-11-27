static int cj_cb_null(void *ctx) {
  cj_advance_array(ctx);
  return CJ_CB_CONTINUE;
}