static reg_errcode_t
internal_function
sift_states_bkref (const re_match_context_t *mctx, re_sift_context_t *sctx,
		   int str_idx, const re_node_set *candidates)
{
  const re_dfa_t *const dfa = mctx->dfa;
  reg_errcode_t err;
  int node_idx, node;
  re_sift_context_t local_sctx;
  int first_idx = search_cur_bkref_entry (mctx, str_idx);

  if (first_idx == -1)
    return REG_NOERROR;

  local_sctx.sifted_states = NULL; /* Mark that it hasn't been initialized.  */

  for (node_idx = 0; node_idx < candidates->nelem; ++node_idx)
    {
      int enabled_idx;
      re_token_type_t type;
      struct re_backref_cache_entry *entry;
      node = candidates->elems[node_idx];
      type = dfa->nodes[node].type;
      /* Avoid infinite loop for the REs like "()\1+".  */
      if (node == sctx->last_node && str_idx == sctx->last_str_idx)
	continue;
      if (type != OP_BACK_REF)
	continue;

      entry = mctx->bkref_ents + first_idx;
      enabled_idx = first_idx;
      do
	{
	  int subexp_len;
	  int to_idx;
	  int dst_node;
	  int ret;
	  re_dfastate_t *cur_state;

	  if (entry->node != node)
	    continue;
	  subexp_len = entry->subexp_to - entry->subexp_from;
	  to_idx = str_idx + subexp_len;
	  dst_node = (subexp_len ? dfa->nexts[node]
		      : dfa->edests[node].elems[0]);

	  if (to_idx > sctx->last_str_idx
	      || sctx->sifted_states[to_idx] == NULL
	      || !STATE_NODE_CONTAINS (sctx->sifted_states[to_idx], dst_node)
	      || check_dst_limits (mctx, &sctx->limits, node,
				   str_idx, dst_node, to_idx))
	    continue;

	  if (local_sctx.sifted_states == NULL)
	    {
	      local_sctx = *sctx;
	      err = re_node_set_init_copy (&local_sctx.limits, &sctx->limits);
	      if (BE (err != REG_NOERROR, 0))
		goto free_return;
	    }
	  local_sctx.last_node = node;
	  local_sctx.last_str_idx = str_idx;
	  ret = re_node_set_insert (&local_sctx.limits, enabled_idx);
	  if (BE (ret < 0, 0))
	    {
	      err = REG_ESPACE;
	      goto free_return;
	    }
	  cur_state = local_sctx.sifted_states[str_idx];
	  err = sift_states_backward (mctx, &local_sctx);
	  if (BE (err != REG_NOERROR, 0))
	    goto free_return;
	  if (sctx->limited_states != NULL)
	    {
	      err = merge_state_array (dfa, sctx->limited_states,
				       local_sctx.sifted_states,
				       str_idx + 1);
	      if (BE (err != REG_NOERROR, 0))
		goto free_return;
	    }
	  local_sctx.sifted_states[str_idx] = cur_state;
	  re_node_set_remove (&local_sctx.limits, enabled_idx);

	  /* mctx->bkref_ents may have changed, reload the pointer.  */
	  entry = mctx->bkref_ents + enabled_idx;
	}
      while (enabled_idx++, entry++->more);
    }
  err = REG_NOERROR;
 free_return:
  if (local_sctx.sifted_states != NULL)
    {
      re_node_set_free (&local_sctx.limits);
    }

  return err;
}