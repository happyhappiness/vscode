static int cj_cb_boolean (void * ctx, int boolVal)
{
  cj_cb_inc_array_index (ctx, /* update_key = */ 0);
  return (CJ_CB_CONTINUE);
}