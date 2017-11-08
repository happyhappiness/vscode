static reg_errcode_t
internal_function
expand_bkref_cache (re_match_context_t *mctx, re_node_set *cur_nodes,
		    int cur_str, int subexp_num, int type)
{
  const re_dfa_t *const dfa = mctx->dfa;
  reg_errcode_t err;
  int cache_idx_start = search_cur_bkref_entry (mctx, cur_str);
  struct re_backref_cache_entry *ent;

  if (cache_idx_start == -1)
    return REG_NOERROR;

 restart:
  ent = mctx->bkref_ents + cache_idx_start;
  do
    {
      int to_idx, next_node;

      /* Is this entry ENT is appropriate?  */
      if (!re_node_set_contains (cur_nodes, ent->node))
	continue; /* No.  */

      to_idx = cur_str + ent->subexp_to - ent->subexp_from;
      /* Calculate the destination of the back reference, and append it
	 to MCTX->STATE_LOG.  */
      if (to_idx == cur_str)
	{
	  /* The backreference did epsilon transit, we must re-check all the
	     node in the current state.  */
	  re_node_set new_dests;
	  reg_errcode_t err2, err3;
	  next_node = dfa->edests[ent->node].elems[0];
	  if (re_node_set_contains (cur_nodes, next_node))
	    continue;
	  err = re_node_set_init_1 (&new_dests, next_node);
	  err2 = check_arrival_expand_ecl (dfa, &new_dests, subexp_num, type);
	  err3 = re_node_set_merge (cur_nodes, &new_dests);
	  re_node_set_free (&new_dests);
	  if (BE (err != REG_NOERROR || err2 != REG_NOERROR
		  || err3 != REG_NOERROR, 0))
	    {
	      err = (err != REG_NOERROR ? err
		     : (err2 != REG_NOERROR ? err2 : err3));
	      return err;
	    }
	  /* TODO: It is still inefficient...  */
	  goto restart;
	}
      else
	{
	  re_node_set union_set;
	  next_node = dfa->nexts[ent->node];
	  if (mctx->state_log[to_idx])
	    {
	      int ret;
	      if (re_node_set_contains (&mctx->state_log[to_idx]->nodes,
					next_node))
		continue;
	      err = re_node_set_init_copy (&union_set,
					   &mctx->state_log[to_idx]->nodes);
	      ret = re_node_set_insert (&union_set, next_node);
	      if (BE (err != REG_NOERROR || ret < 0, 0))
		{
		  re_node_set_free (&union_set);
		  err = err != REG_NOERROR ? err : REG_ESPACE;
		  return err;
		}
	    }
	  else
	    {
	      err = re_node_set_init_1 (&union_set, next_node);
	      if (BE (err != REG_NOERROR, 0))
		return err;
	    }
	  mctx->state_log[to_idx] = re_acquire_state (&err, dfa, &union_set);
	  re_node_set_free (&union_set);
	  if (BE (mctx->state_log[to_idx] == NULL
		  && err != REG_NOERROR, 0))
	    return err;
	}
    }
  while (ent++->more);
  return REG_NOERROR;
}