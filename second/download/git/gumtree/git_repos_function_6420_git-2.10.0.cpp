static reg_errcode_t
internal_function
update_cur_sifted_state (const re_match_context_t *mctx,
			 re_sift_context_t *sctx, int str_idx,
			 re_node_set *dest_nodes)
{
  const re_dfa_t *const dfa = mctx->dfa;
  reg_errcode_t err = REG_NOERROR;
  const re_node_set *candidates;
  candidates = ((mctx->state_log[str_idx] == NULL) ? NULL
		: &mctx->state_log[str_idx]->nodes);

  if (dest_nodes->nelem == 0)
    sctx->sifted_states[str_idx] = NULL;
  else
    {
      if (candidates)
	{
	  /* At first, add the nodes which can epsilon transit to a node in
	     DEST_NODE.  */
	  err = add_epsilon_src_nodes (dfa, dest_nodes, candidates);
	  if (BE (err != REG_NOERROR, 0))
	    return err;

	  /* Then, check the limitations in the current sift_context.  */
	  if (sctx->limits.nelem)
	    {
	      err = check_subexp_limits (dfa, dest_nodes, candidates, &sctx->limits,
					 mctx->bkref_ents, str_idx);
	      if (BE (err != REG_NOERROR, 0))
		return err;
	    }
	}

      sctx->sifted_states[str_idx] = re_acquire_state (&err, dfa, dest_nodes);
      if (BE (err != REG_NOERROR, 0))
	return err;
    }

  if (candidates && mctx->state_log[str_idx]->has_backref)
    {
      err = sift_states_bkref (mctx, sctx, str_idx, candidates);
      if (BE (err != REG_NOERROR, 0))
	return err;
    }
  return REG_NOERROR;
}