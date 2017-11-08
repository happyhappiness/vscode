static reg_errcode_t
internal_function
sift_states_backward (const re_match_context_t *mctx, re_sift_context_t *sctx)
{
  reg_errcode_t err;
  int null_cnt = 0;
  int str_idx = sctx->last_str_idx;
  re_node_set cur_dest;

#ifdef DEBUG
  assert (mctx->state_log != NULL && mctx->state_log[str_idx] != NULL);
#endif

  /* Build sifted state_log[str_idx].  It has the nodes which can epsilon
     transit to the last_node and the last_node itself.  */
  err = re_node_set_init_1 (&cur_dest, sctx->last_node);
  if (BE (err != REG_NOERROR, 0))
    return err;
  err = update_cur_sifted_state (mctx, sctx, str_idx, &cur_dest);
  if (BE (err != REG_NOERROR, 0))
    goto free_return;

  /* Then check each states in the state_log.  */
  while (str_idx > 0)
    {
      /* Update counters.  */
      null_cnt = (sctx->sifted_states[str_idx] == NULL) ? null_cnt + 1 : 0;
      if (null_cnt > mctx->max_mb_elem_len)
	{
	  memset (sctx->sifted_states, '\0',
		  sizeof (re_dfastate_t *) * str_idx);
	  re_node_set_free (&cur_dest);
	  return REG_NOERROR;
	}
      re_node_set_empty (&cur_dest);
      --str_idx;

      if (mctx->state_log[str_idx])
	{
	  err = build_sifted_states (mctx, sctx, str_idx, &cur_dest);
	  if (BE (err != REG_NOERROR, 0))
	    goto free_return;
	}

      /* Add all the nodes which satisfy the following conditions:
	 - It can epsilon transit to a node in CUR_DEST.
	 - It is in CUR_SRC.
	 And update state_log.  */
      err = update_cur_sifted_state (mctx, sctx, str_idx, &cur_dest);
      if (BE (err != REG_NOERROR, 0))
	goto free_return;
    }
  err = REG_NOERROR;
 free_return:
  re_node_set_free (&cur_dest);
  return err;
}