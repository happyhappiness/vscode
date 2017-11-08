static reg_errcode_t
internal_function
set_regs (const regex_t *preg, const re_match_context_t *mctx, size_t nmatch,
	  regmatch_t *pmatch, int fl_backtrack)
{
  const re_dfa_t *dfa = (const re_dfa_t *) preg->buffer;
  int idx, cur_node;
  re_node_set eps_via_nodes;
  struct re_fail_stack_t *fs;
  struct re_fail_stack_t fs_body = { 0, 2, NULL };
  regmatch_t *prev_idx_match;
  int prev_idx_match_malloced = 0;

#ifdef DEBUG
  assert (nmatch > 1);
  assert (mctx->state_log != NULL);
#endif
  if (fl_backtrack)
    {
      fs = &fs_body;
      fs->stack = re_malloc (struct re_fail_stack_ent_t, fs->alloc);
      if (fs->stack == NULL)
	return REG_ESPACE;
    }
  else
    fs = NULL;

  cur_node = dfa->init_node;
  re_node_set_init_empty (&eps_via_nodes);

#ifdef HAVE_ALLOCA
  if (__libc_use_alloca (nmatch * sizeof (regmatch_t)))
    prev_idx_match = (regmatch_t *) alloca (nmatch * sizeof (regmatch_t));
  else
#endif
    {
      prev_idx_match = re_malloc (regmatch_t, nmatch);
      if (prev_idx_match == NULL)
	{
	  free_fail_stack_return (fs);
	  return REG_ESPACE;
	}
      prev_idx_match_malloced = 1;
    }
  memcpy (prev_idx_match, pmatch, sizeof (regmatch_t) * nmatch);

  for (idx = pmatch[0].rm_so; idx <= pmatch[0].rm_eo ;)
    {
      update_regs (dfa, pmatch, prev_idx_match, cur_node, idx, nmatch);

      if (idx == pmatch[0].rm_eo && cur_node == mctx->last_node)
	{
	  int reg_idx;
	  if (fs)
	    {
	      for (reg_idx = 0; reg_idx < nmatch; ++reg_idx)
		if (pmatch[reg_idx].rm_so > -1 && pmatch[reg_idx].rm_eo == -1)
		  break;
	      if (reg_idx == nmatch)
		{
		  re_node_set_free (&eps_via_nodes);
		  if (prev_idx_match_malloced)
		    re_free (prev_idx_match);
		  return free_fail_stack_return (fs);
		}
	      cur_node = pop_fail_stack (fs, &idx, nmatch, pmatch,
					 &eps_via_nodes);
	    }
	  else
	    {
	      re_node_set_free (&eps_via_nodes);
	      if (prev_idx_match_malloced)
		re_free (prev_idx_match);
	      return REG_NOERROR;
	    }
	}

      /* Proceed to next node.  */
      cur_node = proceed_next_node (mctx, nmatch, pmatch, &idx, cur_node,
				    &eps_via_nodes, fs);

      if (BE (cur_node < 0, 0))
	{
	  if (BE (cur_node == -2, 0))
	    {
	      re_node_set_free (&eps_via_nodes);
	      if (prev_idx_match_malloced)
		re_free (prev_idx_match);
	      free_fail_stack_return (fs);
	      return REG_ESPACE;
	    }
	  if (fs)
	    cur_node = pop_fail_stack (fs, &idx, nmatch, pmatch,
				       &eps_via_nodes);
	  else
	    {
	      re_node_set_free (&eps_via_nodes);
	      if (prev_idx_match_malloced)
		re_free (prev_idx_match);
	      return REG_NOMATCH;
	    }
	}
    }
  re_node_set_free (&eps_via_nodes);
  if (prev_idx_match_malloced)
    re_free (prev_idx_match);
  return free_fail_stack_return (fs);
}