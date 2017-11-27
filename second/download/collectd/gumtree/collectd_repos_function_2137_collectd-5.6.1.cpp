static int cj_cb_start_map (void *ctx)
{
  cj_cb_inc_array_index (ctx, /* update_key = */ 1);
  return cj_cb_start (ctx);
}