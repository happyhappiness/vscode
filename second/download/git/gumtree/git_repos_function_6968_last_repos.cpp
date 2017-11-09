static reg_errcode_t
internal_function
check_subexp_matching_top (re_match_context_t *mctx, re_node_set *cur_nodes,
			   int str_idx)
{
  const re_dfa_t *const dfa = mctx->dfa;
  int node_idx;
  reg_errcode_t err;

  /* TODO: This isn't efficient.
	   Because there might be more than one nodes whose types are
	   OP_OPEN_SUBEXP and whose index is SUBEXP_IDX, we must check all
	   nodes.
	   E.g. RE: (a){2}  */
  for (node_idx = 0; node_idx < cur_nodes->nelem; ++node_idx)
    {
      int node = cur_nodes->elems[node_idx];
      if (dfa->nodes[node].type == OP_OPEN_SUBEXP
	  && dfa->nodes[node].opr.idx < BITSET_WORD_BITS
	  && (dfa->used_bkref_map
	      & ((bitset_word_t) 1 << dfa->nodes[node].opr.idx)))
	{
	  err = match_ctx_add_subtop (mctx, node, str_idx);
	  if (BE (err != REG_NOERROR, 0))
	    return err;
	}
    }
  return REG_NOERROR;
}