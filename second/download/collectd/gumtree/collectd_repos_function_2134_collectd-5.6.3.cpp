static int cj_cb_boolean(void *ctx, int boolVal) {
  cj_advance_array(ctx);
  return (CJ_CB_CONTINUE);
}