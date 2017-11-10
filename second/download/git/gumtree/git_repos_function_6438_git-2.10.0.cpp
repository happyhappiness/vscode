static reg_errcode_t
internal_function
check_arrival (re_match_context_t *mctx, state_array_t *path, int top_node,
	       int top_str, int last_node, int last_str, int type)
{
  const re_dfa_t *const dfa = mctx->dfa;
  reg_errcode_t err = REG_NOERROR;
  int subexp_num, backup_cur_idx, str_idx, null_cnt;
  re_dfastate_t *cur_state = NULL;
  re_node_set *cur_nodes, next_nodes;
  re_dfastate_t **backup_state_log;
  unsigned int context;

  subexp_num = dfa->nodes[top_node].opr.idx;
  /* Extend the buffer if we need.  */
  if (BE (path->alloc < last_str + mctx->max_mb_elem_len + 1, 0))
    {
      re_dfastate_t **new_array;
      int old_alloc = path->alloc;
      path->alloc += last_str + mctx->max_mb_elem_len + 1;
      new_array = re_realloc (path->array, re_dfastate_t *, path->alloc);
      if (BE (new_array == NULL, 0))
	{
	  path->alloc = old_alloc;
	  return REG_ESPACE;
	}
      path->array = new_array;
      memset (new_array + old_alloc, '\0',
	      sizeof (re_dfastate_t *) * (path->alloc - old_alloc));
    }

  str_idx = path->next_idx ? path->next_idx : top_str;

  /* Temporary modify MCTX.  */
  backup_state_log = mctx->state_log;
  backup_cur_idx = mctx->input.cur_idx;
  mctx->state_log = path->array;
  mctx->input.cur_idx = str_idx;

  /* Setup initial node set.  */
  context = re_string_context_at (&mctx->input, str_idx - 1, mctx->eflags);
  if (str_idx == top_str)
    {
      err = re_node_set_init_1 (&next_nodes, top_node);
      if (BE (err != REG_NOERROR, 0))
	return err;
      err = check_arrival_expand_ecl (dfa, &next_nodes, subexp_num, type);
      if (BE (err != REG_NOERROR, 0))
	{
	  re_node_set_free (&next_nodes);
	  return err;
	}
    }
  else
    {
      cur_state = mctx->state_log[str_idx];
      if (cur_state && cur_state->has_backref)
	{
	  err = re_node_set_init_copy (&next_nodes, &cur_state->nodes);
	  if (BE (err != REG_NOERROR, 0))
	    return err;
	}
      else
	re_node_set_init_empty (&next_nodes);
    }
  if (str_idx == top_str || (cur_state && cur_state->has_backref))
    {
      if (next_nodes.nelem)
	{
	  err = expand_bkref_cache (mctx, &next_nodes, str_idx,
				    subexp_num, type);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&next_nodes);
	      return err;
	    }
	}
      cur_state = re_acquire_state_context (&err, dfa, &next_nodes, context);
      if (BE (cur_state == NULL && err != REG_NOERROR, 0))
	{
	  re_node_set_free (&next_nodes);
	  return err;
	}
      mctx->state_log[str_idx] = cur_state;
    }

  for (null_cnt = 0; str_idx < last_str && null_cnt <= mctx->max_mb_elem_len;)
    {
      re_node_set_empty (&next_nodes);
      if (mctx->state_log[str_idx + 1])
	{
	  err = re_node_set_merge (&next_nodes,
				   &mctx->state_log[str_idx + 1]->nodes);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&next_nodes);
	      return err;
	    }
	}
      if (cur_state)
	{
	  err = check_arrival_add_next_nodes (mctx, str_idx,
					      &cur_state->non_eps_nodes,
					      &next_nodes);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&next_nodes);
	      return err;
	    }
	}
      ++str_idx;
      if (next_nodes.nelem)
	{
	  err = check_arrival_expand_ecl (dfa, &next_nodes, subexp_num, type);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&next_nodes);
	      return err;
	    }
	  err = expand_bkref_cache (mctx, &next_nodes, str_idx,
				    subexp_num, type);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&next_nodes);
	      return err;
	    }
	}
      context = re_string_context_at (&mctx->input, str_idx - 1, mctx->eflags);
      cur_state = re_acquire_state_context (&err, dfa, &next_nodes, context);
      if (BE (cur_state == NULL && err != REG_NOERROR, 0))
	{
	  re_node_set_free (&next_nodes);
	  return err;
	}
      mctx->state_log[str_idx] = cur_state;
      null_cnt = cur_state == NULL ? null_cnt + 1 : 0;
    }
  re_node_set_free (&next_nodes);
  cur_nodes = (mctx->state_log[last_str] == NULL ? NULL
	       : &mctx->state_log[last_str]->nodes);
  path->next_idx = str_idx;

  /* Fix MCTX.  */
  mctx->state_log = backup_state_log;
  mctx->input.cur_idx = backup_cur_idx;

  /* Then check the current node set has the node LAST_NODE.  */
  if (cur_nodes != NULL && re_node_set_contains (cur_nodes, last_node))
    return REG_NOERROR;

  return REG_NOMATCH;
}