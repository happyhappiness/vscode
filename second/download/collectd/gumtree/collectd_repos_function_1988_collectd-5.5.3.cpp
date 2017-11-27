static int cj_cb_end (void *ctx)
{
  cj_t *db = (cj_t *)ctx;
  db->state[db->depth].tree = NULL;
  --db->depth;
  return (CJ_CB_CONTINUE);
}