static reg_errcode_t
internal_function
check_arrival_add_next_nodes (re_match_context_t *mctx, int str_idx,
			      re_node_set *cur_nodes, re_node_set *next_nodes)
{
  const re_dfa_t *const dfa = mctx->dfa;
  int result;
  int cur_idx;
#ifdef RE_ENABLE_I18N
  reg_errcode_t err = REG_NOERROR;
#endif
  re_node_set union_set;
  re_node_set_init_empty (&union_set);
  for (cur_idx = 0; cur_idx < cur_nodes->nelem; ++cur_idx)
    {
      int naccepted = 0;
      int cur_node = cur_nodes->elems[cur_idx];
#ifdef DEBUG
      re_token_type_t type = dfa->nodes[cur_node].type;
      assert (!IS_EPSILON_NODE (type));
#endif
#ifdef RE_ENABLE_I18N
      /* If the node may accept `multi byte'.  */
      if (dfa->nodes[cur_node].accept_mb)
	{
	  naccepted = check_node_accept_bytes (dfa, cur_node, &mctx->input,
					       str_idx);
	  if (naccepted > 1)
	    {
	      re_dfastate_t *dest_state;
	      int next_node = dfa->nexts[cur_node];
	      int next_idx = str_idx + naccepted;
	      dest_state = mctx->state_log[next_idx];
	      re_node_set_empty (&union_set);
	      if (dest_state)
		{
		  err = re_node_set_merge (&union_set, &dest_state->nodes);
		  if (BE (err != REG_NOERROR, 0))
		    {
		      re_node_set_free (&union_set);
		      return err;
		    }
		}
	      result = re_node_set_insert (&union_set, next_node);
	      if (BE (result < 0, 0))
		{
		  re_node_set_free (&union_set);
		  return REG_ESPACE;
		}
	      mctx->state_log[next_idx] = re_acquire_state (&err, dfa,
							    &union_set);
	      if (BE (mctx->state_log[next_idx] == NULL
		      && err != REG_NOERROR, 0))
		{
		  re_node_set_free (&union_set);
		  return err;
		}
	    }
	}
#endif /* RE_ENABLE_I18N */
      if (naccepted
	  || check_node_accept (mctx, dfa->nodes + cur_node, str_idx))
	{
	  result = re_node_set_insert (next_nodes, dfa->nexts[cur_node]);
	  if (BE (result < 0, 0))
	    {
	      re_node_set_free (&union_set);
	      return REG_ESPACE;
	    }
	}
    }
  re_node_set_free (&union_set);
  return REG_NOERROR;
}