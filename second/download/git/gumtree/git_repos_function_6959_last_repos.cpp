static int
internal_function
check_dst_limits (const re_match_context_t *mctx, re_node_set *limits,
		  int dst_node, int dst_idx, int src_node, int src_idx)
{
  const re_dfa_t *const dfa = mctx->dfa;
  int lim_idx, src_pos, dst_pos;

  int dst_bkref_idx = search_cur_bkref_entry (mctx, dst_idx);
  int src_bkref_idx = search_cur_bkref_entry (mctx, src_idx);
  for (lim_idx = 0; lim_idx < limits->nelem; ++lim_idx)
    {
      int subexp_idx;
      struct re_backref_cache_entry *ent;
      ent = mctx->bkref_ents + limits->elems[lim_idx];
      subexp_idx = dfa->nodes[ent->node].opr.idx;

      dst_pos = check_dst_limits_calc_pos (mctx, limits->elems[lim_idx],
					   subexp_idx, dst_node, dst_idx,
					   dst_bkref_idx);
      src_pos = check_dst_limits_calc_pos (mctx, limits->elems[lim_idx],
					   subexp_idx, src_node, src_idx,
					   src_bkref_idx);

      /* In case of:
	 <src> <dst> ( <subexp> )
	 ( <subexp> ) <src> <dst>
	 ( <subexp1> <src> <subexp2> <dst> <subexp3> )  */
      if (src_pos == dst_pos)
	continue; /* This is unrelated limitation.  */
      else
	return 1;
    }
  return 0;
}