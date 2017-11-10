static int
internal_function
find_subexp_node (const re_dfa_t *dfa, const re_node_set *nodes,
		  int subexp_idx, int type)
{
  int cls_idx;
  for (cls_idx = 0; cls_idx < nodes->nelem; ++cls_idx)
    {
      int cls_node = nodes->elems[cls_idx];
      const re_token_t *node = dfa->nodes + cls_node;
      if (node->type == type
	  && node->opr.idx == subexp_idx)
	return cls_node;
    }
  return -1;
}