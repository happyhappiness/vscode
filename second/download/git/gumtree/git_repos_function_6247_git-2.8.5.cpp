static int
internal_function
check_matching (re_match_context_t *mctx, int fl_longest_match,
		int *p_match_first)
{
  const re_dfa_t *const dfa = mctx->dfa;
  reg_errcode_t err;
  int match = 0;
  int match_last = -1;
  int cur_str_idx = re_string_cur_idx (&mctx->input);
  re_dfastate_t *cur_state;
  int at_init_state = p_match_first != NULL;
  int next_start_idx = cur_str_idx;

  err = REG_NOERROR;
  cur_state = acquire_init_state_context (&err, mctx, cur_str_idx);
  /* An initial state must not be NULL (invalid).  */
  if (BE (cur_state == NULL, 0))
    {
      assert (err == REG_ESPACE);
      return -2;
    }

  if (mctx->state_log != NULL)
    {
      mctx->state_log[cur_str_idx] = cur_state;

      /* Check OP_OPEN_SUBEXP in the initial state in case that we use them
	 later.  E.g. Processing back references.  */
      if (BE (dfa->nbackref, 0))
	{
	  at_init_state = 0;
	  err = check_subexp_matching_top (mctx, &cur_state->nodes, 0);
	  if (BE (err != REG_NOERROR, 0))
	    return err;

	  if (cur_state->has_backref)
	    {
	      err = transit_state_bkref (mctx, &cur_state->nodes);
	      if (BE (err != REG_NOERROR, 0))
		return err;
	    }
	}
    }

  /* If the RE accepts NULL string.  */
  if (BE (cur_state->halt, 0))
    {
      if (!cur_state->has_constraint
	  || check_halt_state_context (mctx, cur_state, cur_str_idx))
	{
	  if (!fl_longest_match)
	    return cur_str_idx;
	  else
	    {
	      match_last = cur_str_idx;
	      match = 1;
	    }
	}
    }

  while (!re_string_eoi (&mctx->input))
    {
      re_dfastate_t *old_state = cur_state;
      int next_char_idx = re_string_cur_idx (&mctx->input) + 1;

      if (BE (next_char_idx >= mctx->input.bufs_len, 0)
	  || (BE (next_char_idx >= mctx->input.valid_len, 0)
	      && mctx->input.valid_len < mctx->input.len))
	{
	  err = extend_buffers (mctx);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      assert (err == REG_ESPACE);
	      return -2;
	    }
	}

      cur_state = transit_state (&err, mctx, cur_state);
      if (mctx->state_log != NULL)
	cur_state = merge_state_with_log (&err, mctx, cur_state);

      if (cur_state == NULL)
	{
	  /* Reached the invalid state or an error.  Try to recover a valid
	     state using the state log, if available and if we have not
	     already found a valid (even if not the longest) match.  */
	  if (BE (err != REG_NOERROR, 0))
	    return -2;

	  if (mctx->state_log == NULL
	      || (match && !fl_longest_match)
	      || (cur_state = find_recover_state (&err, mctx)) == NULL)
	    break;
	}

      if (BE (at_init_state, 0))
	{
	  if (old_state == cur_state)
	    next_start_idx = next_char_idx;
	  else
	    at_init_state = 0;
	}

      if (cur_state->halt)
	{
	  /* Reached a halt state.
	     Check the halt state can satisfy the current context.  */
	  if (!cur_state->has_constraint
	      || check_halt_state_context (mctx, cur_state,
					   re_string_cur_idx (&mctx->input)))
	    {
	      /* We found an appropriate halt state.  */
	      match_last = re_string_cur_idx (&mctx->input);
	      match = 1;

	      /* We found a match, do not modify match_first below.  */
	      p_match_first = NULL;
	      if (!fl_longest_match)
		break;
	    }
	}
    }

  if (p_match_first)
    *p_match_first += next_start_idx;

  return match_last;
}