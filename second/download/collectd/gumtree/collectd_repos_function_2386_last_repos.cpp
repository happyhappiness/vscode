static int cj_cb_boolean(void *ctx, int boolVal) {
  if (boolVal)
    return cj_cb_number(ctx, "1", 1);
  else
    return cj_cb_number(ctx, "0", 1);
}