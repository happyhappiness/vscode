static reg_errcode_t
internal_function
check_arrival_expand_ecl_sub (const re_dfa_t *dfa, re_node_set *dst_nodes,
			      int target, int ex_subexp, int type)
{
  int cur_node;
  for (cur_node = target; !re_node_set_contains (dst_nodes, cur_node);)
    {
      int err;

      if (dfa->nodes[cur_node].type == type
	  && dfa->nodes[cur_node].opr.idx == ex_subexp)
	{
	  if (type == OP_CLOSE_SUBEXP)
	    {
	      err = re_node_set_insert (dst_nodes, cur_node);
	      if (BE (err == -1, 0))
		return REG_ESPACE;
	    }
	  break;
	}
      err = re_node_set_insert (dst_nodes, cur_node);
      if (BE (err == -1, 0))
	return REG_ESPACE;
      if (dfa->edests[cur_node].nelem == 0)
	break;
      if (dfa->edests[cur_node].nelem == 2)
	{
	  err = check_arrival_expand_ecl_sub (dfa, dst_nodes,
					      dfa->edests[cur_node].elems[1],
					      ex_subexp, type);
	  if (BE (err != REG_NOERROR, 0))
	    return err;
	}
      cur_node = dfa->edests[cur_node].elems[0];
    }
  return REG_NOERROR;
}