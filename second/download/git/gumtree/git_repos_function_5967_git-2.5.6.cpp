static reg_errcode_t
internal_function
transit_state_mb (re_match_context_t *mctx, re_dfastate_t *pstate)
{
  const re_dfa_t *const dfa = mctx->dfa;
  reg_errcode_t err;
  int i;

  for (i = 0; i < pstate->nodes.nelem; ++i)
    {
      re_node_set dest_nodes, *new_nodes;
      int cur_node_idx = pstate->nodes.elems[i];
      int naccepted, dest_idx;
      unsigned int context;
      re_dfastate_t *dest_state;

      if (!dfa->nodes[cur_node_idx].accept_mb)
	continue;

      if (dfa->nodes[cur_node_idx].constraint)
	{
	  context = re_string_context_at (&mctx->input,
					  re_string_cur_idx (&mctx->input),
					  mctx->eflags);
	  if (NOT_SATISFY_NEXT_CONSTRAINT (dfa->nodes[cur_node_idx].constraint,
					   context))
	    continue;
	}

      /* How many bytes the node can accept?  */
      naccepted = check_node_accept_bytes (dfa, cur_node_idx, &mctx->input,
					   re_string_cur_idx (&mctx->input));
      if (naccepted == 0)
	continue;

      /* The node can accepts `naccepted' bytes.  */
      dest_idx = re_string_cur_idx (&mctx->input) + naccepted;
      mctx->max_mb_elem_len = ((mctx->max_mb_elem_len < naccepted) ? naccepted
			       : mctx->max_mb_elem_len);
      err = clean_state_log_if_needed (mctx, dest_idx);
      if (BE (err != REG_NOERROR, 0))
	return err;
#ifdef DEBUG
      assert (dfa->nexts[cur_node_idx] != -1);
#endif
      new_nodes = dfa->eclosures + dfa->nexts[cur_node_idx];

      dest_state = mctx->state_log[dest_idx];
      if (dest_state == NULL)
	dest_nodes = *new_nodes;
      else
	{
	  err = re_node_set_init_union (&dest_nodes,
					dest_state->entrance_nodes, new_nodes);
	  if (BE (err != REG_NOERROR, 0))
	    return err;
	}
      context = re_string_context_at (&mctx->input, dest_idx - 1,
				      mctx->eflags);
      mctx->state_log[dest_idx]
	= re_acquire_state_context (&err, dfa, &dest_nodes, context);
      if (dest_state != NULL)
	re_node_set_free (&dest_nodes);
      if (BE (mctx->state_log[dest_idx] == NULL && err != REG_NOERROR, 0))
	return err;
    }
  return REG_NOERROR;
}