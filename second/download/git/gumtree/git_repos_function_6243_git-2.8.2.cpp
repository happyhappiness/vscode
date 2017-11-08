static int
internal_function
proceed_next_node (const re_match_context_t *mctx, int nregs, regmatch_t *regs,
		   int *pidx, int node, re_node_set *eps_via_nodes,
		   struct re_fail_stack_t *fs)
{
  const re_dfa_t *const dfa = mctx->dfa;
  int i, err;
  if (IS_EPSILON_NODE (dfa->nodes[node].type))
    {
      re_node_set *cur_nodes = &mctx->state_log[*pidx]->nodes;
      re_node_set *edests = &dfa->edests[node];
      int dest_node;
      err = re_node_set_insert (eps_via_nodes, node);
      if (BE (err < 0, 0))
	return -2;
      /* Pick up a valid destination, or return -1 if none is found.  */
      for (dest_node = -1, i = 0; i < edests->nelem; ++i)
	{
	  int candidate = edests->elems[i];
	  if (!re_node_set_contains (cur_nodes, candidate))
	    continue;
	  if (dest_node == -1)
	    dest_node = candidate;

	  else
	    {
	      /* In order to avoid infinite loop like "(a*)*", return the second
		 epsilon-transition if the first was already considered.  */
	      if (re_node_set_contains (eps_via_nodes, dest_node))
		return candidate;

	      /* Otherwise, push the second epsilon-transition on the fail stack.  */
	      else if (fs != NULL
		       && push_fail_stack (fs, *pidx, candidate, nregs, regs,
					   eps_via_nodes))
		return -2;

	      /* We know we are going to exit.  */
	      break;
	    }
	}
      return dest_node;
    }
  else
    {
      int naccepted = 0;
      re_token_type_t type = dfa->nodes[node].type;

#ifdef RE_ENABLE_I18N
      if (dfa->nodes[node].accept_mb)
	naccepted = check_node_accept_bytes (dfa, node, &mctx->input, *pidx);
      else
#endif /* RE_ENABLE_I18N */
      if (type == OP_BACK_REF)
	{
	  int subexp_idx = dfa->nodes[node].opr.idx + 1;
	  naccepted = regs[subexp_idx].rm_eo - regs[subexp_idx].rm_so;
	  if (fs != NULL)
	    {
	      if (regs[subexp_idx].rm_so == -1 || regs[subexp_idx].rm_eo == -1)
		return -1;
	      else if (naccepted)
		{
		  char *buf = (char *) re_string_get_buffer (&mctx->input);
		  if (memcmp (buf + regs[subexp_idx].rm_so, buf + *pidx,
			      naccepted) != 0)
		    return -1;
		}
	    }

	  if (naccepted == 0)
	    {
	      int dest_node;
	      err = re_node_set_insert (eps_via_nodes, node);
	      if (BE (err < 0, 0))
		return -2;
	      dest_node = dfa->edests[node].elems[0];
	      if (re_node_set_contains (&mctx->state_log[*pidx]->nodes,
					dest_node))
		return dest_node;
	    }
	}

      if (naccepted != 0
	  || check_node_accept (mctx, dfa->nodes + node, *pidx))
	{
	  int dest_node = dfa->nexts[node];
	  *pidx = (naccepted == 0) ? *pidx + 1 : *pidx + naccepted;
	  if (fs && (*pidx > mctx->match_last || mctx->state_log[*pidx] == NULL
		     || !re_node_set_contains (&mctx->state_log[*pidx]->nodes,
					       dest_node)))
	    return -1;
	  re_node_set_empty (eps_via_nodes);
	  return dest_node;
	}
    }
  return -1;
}