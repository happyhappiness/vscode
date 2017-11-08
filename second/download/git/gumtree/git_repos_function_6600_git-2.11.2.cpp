static int
internal_function
check_dst_limits_calc_pos_1 (const re_match_context_t *mctx, int boundaries,
			     int subexp_idx, int from_node, int bkref_idx)
{
  const re_dfa_t *const dfa = mctx->dfa;
  const re_node_set *eclosures = dfa->eclosures + from_node;
  int node_idx;

  /* Else, we are on the boundary: examine the nodes on the epsilon
     closure.  */
  for (node_idx = 0; node_idx < eclosures->nelem; ++node_idx)
    {
      int node = eclosures->elems[node_idx];
      switch (dfa->nodes[node].type)
	{
	case OP_BACK_REF:
	  if (bkref_idx != -1)
	    {
	      struct re_backref_cache_entry *ent = mctx->bkref_ents + bkref_idx;
	      do
		{
		  int dst, cpos;

		  if (ent->node != node)
		    continue;

		  if (subexp_idx < BITSET_WORD_BITS
		      && !(ent->eps_reachable_subexps_map
			   & ((bitset_word_t) 1 << subexp_idx)))
		    continue;

		  /* Recurse trying to reach the OP_OPEN_SUBEXP and
		     OP_CLOSE_SUBEXP cases below.  But, if the
		     destination node is the same node as the source
		     node, don't recurse because it would cause an
		     infinite loop: a regex that exhibits this behavior
		     is ()\1*\1*  */
		  dst = dfa->edests[node].elems[0];
		  if (dst == from_node)
		    {
		      if (boundaries & 1)
			return -1;
		      else /* if (boundaries & 2) */
			return 0;
		    }

		  cpos =
		    check_dst_limits_calc_pos_1 (mctx, boundaries, subexp_idx,
						 dst, bkref_idx);
		  if (cpos == -1 /* && (boundaries & 1) */)
		    return -1;
		  if (cpos == 0 && (boundaries & 2))
		    return 0;

		  if (subexp_idx < BITSET_WORD_BITS)
		    ent->eps_reachable_subexps_map
		      &= ~((bitset_word_t) 1 << subexp_idx);
		}
	      while (ent++->more);
	    }
	  break;

	case OP_OPEN_SUBEXP:
	  if ((boundaries & 1) && subexp_idx == dfa->nodes[node].opr.idx)
	    return -1;
	  break;

	case OP_CLOSE_SUBEXP:
	  if ((boundaries & 2) && subexp_idx == dfa->nodes[node].opr.idx)
	    return 0;
	  break;

	default:
	    break;
	}
    }

  return (boundaries & 2) ? 1 : 0;
}