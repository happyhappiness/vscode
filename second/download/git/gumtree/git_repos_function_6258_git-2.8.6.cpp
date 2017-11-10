static reg_errcode_t
internal_function
build_sifted_states (const re_match_context_t *mctx, re_sift_context_t *sctx,
		     int str_idx, re_node_set *cur_dest)
{
  const re_dfa_t *const dfa = mctx->dfa;
  const re_node_set *cur_src = &mctx->state_log[str_idx]->non_eps_nodes;
  int i;

  /* Then build the next sifted state.
     We build the next sifted state on `cur_dest', and update
     `sifted_states[str_idx]' with `cur_dest'.
     Note:
     `cur_dest' is the sifted state from `state_log[str_idx + 1]'.
     `cur_src' points the node_set of the old `state_log[str_idx]'
     (with the epsilon nodes pre-filtered out).  */
  for (i = 0; i < cur_src->nelem; i++)
    {
      int prev_node = cur_src->elems[i];
      int naccepted = 0;
      int ret;

#ifdef DEBUG
      re_token_type_t type = dfa->nodes[prev_node].type;
      assert (!IS_EPSILON_NODE (type));
#endif
#ifdef RE_ENABLE_I18N
      /* If the node may accept `multi byte'.  */
      if (dfa->nodes[prev_node].accept_mb)
	naccepted = sift_states_iter_mb (mctx, sctx, prev_node,
					 str_idx, sctx->last_str_idx);
#endif /* RE_ENABLE_I18N */

      /* We don't check backreferences here.
	 See update_cur_sifted_state().  */
      if (!naccepted
	  && check_node_accept (mctx, dfa->nodes + prev_node, str_idx)
	  && STATE_NODE_CONTAINS (sctx->sifted_states[str_idx + 1],
				  dfa->nexts[prev_node]))
	naccepted = 1;

      if (naccepted == 0)
	continue;

      if (sctx->limits.nelem)
	{
	  int to_idx = str_idx + naccepted;
	  if (check_dst_limits (mctx, &sctx->limits,
				dfa->nexts[prev_node], to_idx,
				prev_node, str_idx))
	    continue;
	}
      ret = re_node_set_insert (cur_dest, prev_node);
      if (BE (ret == -1, 0))
	return REG_ESPACE;
    }

  return REG_NOERROR;
}