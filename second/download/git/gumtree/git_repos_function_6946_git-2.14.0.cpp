static re_dfastate_t *
internal_function
merge_state_with_log (reg_errcode_t *err, re_match_context_t *mctx,
		      re_dfastate_t *next_state)
{
  const re_dfa_t *const dfa = mctx->dfa;
  int cur_idx = re_string_cur_idx (&mctx->input);

  if (cur_idx > mctx->state_log_top)
    {
      mctx->state_log[cur_idx] = next_state;
      mctx->state_log_top = cur_idx;
    }
  else if (mctx->state_log[cur_idx] == NULL)
    {
      mctx->state_log[cur_idx] = next_state;
    }
  else
    {
      re_dfastate_t *pstate;
      unsigned int context;
      re_node_set next_nodes, *log_nodes, *table_nodes = NULL;
      /* If (state_log[cur_idx] != 0), it implies that cur_idx is
	 the destination of a multibyte char/collating element/
	 back reference.  Then the next state is the union set of
	 these destinations and the results of the transition table.  */
      pstate = mctx->state_log[cur_idx];
      log_nodes = pstate->entrance_nodes;
      if (next_state != NULL)
	{
	  table_nodes = next_state->entrance_nodes;
	  *err = re_node_set_init_union (&next_nodes, table_nodes,
					     log_nodes);
	  if (BE (*err != REG_NOERROR, 0))
	    return NULL;
	}
      else
	next_nodes = *log_nodes;
      /* Note: We already add the nodes of the initial state,
	 then we don't need to add them here.  */

      context = re_string_context_at (&mctx->input,
				      re_string_cur_idx (&mctx->input) - 1,
				      mctx->eflags);
      next_state = mctx->state_log[cur_idx]
	= re_acquire_state_context (err, dfa, &next_nodes, context);
      /* We don't need to check errors here, since the return value of
	 this function is next_state and ERR is already set.  */

      if (table_nodes != NULL)
	re_node_set_free (&next_nodes);
    }

  if (BE (dfa->nbackref, 0) && next_state != NULL)
    {
      /* Check OP_OPEN_SUBEXP in the current state in case that we use them
	 later.  We must check them here, since the back references in the
	 next state might use them.  */
      *err = check_subexp_matching_top (mctx, &next_state->nodes,
					cur_idx);
      if (BE (*err != REG_NOERROR, 0))
	return NULL;

      /* If the next state has back references.  */
      if (next_state->has_backref)
	{
	  *err = transit_state_bkref (mctx, &next_state->nodes);
	  if (BE (*err != REG_NOERROR, 0))
	    return NULL;
	  next_state = mctx->state_log[cur_idx];
	}
    }

  return next_state;
}