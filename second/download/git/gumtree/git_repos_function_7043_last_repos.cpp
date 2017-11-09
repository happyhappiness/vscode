static reg_errcode_t
mark_opt_subexp (void *extra, bin_tree_t *node)
{
  int idx = (int) (intptr_t) extra;
  if (node->token.type == SUBEXP && node->token.opr.idx == idx)
    node->token.opt_subexp = 1;

  return REG_NOERROR;
}