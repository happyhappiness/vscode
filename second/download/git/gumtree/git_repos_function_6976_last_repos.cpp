static reg_errcode_t
internal_function
check_arrival_expand_ecl (const re_dfa_t *dfa, re_node_set *cur_nodes,
			  int ex_subexp, int type)
{
  reg_errcode_t err;
  int idx, outside_node;
  re_node_set new_nodes;
#ifdef DEBUG
  assert (cur_nodes->nelem);
#endif
  err = re_node_set_alloc (&new_nodes, cur_nodes->nelem);
  if (BE (err != REG_NOERROR, 0))
    return err;
  /* Create a new node set NEW_NODES with the nodes which are epsilon
     closures of the node in CUR_NODES.  */

  for (idx = 0; idx < cur_nodes->nelem; ++idx)
    {
      int cur_node = cur_nodes->elems[idx];
      const re_node_set *eclosure = dfa->eclosures + cur_node;
      outside_node = find_subexp_node (dfa, eclosure, ex_subexp, type);
      if (outside_node == -1)
	{
	  /* There are no problematic nodes, just merge them.  */
	  err = re_node_set_merge (&new_nodes, eclosure);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&new_nodes);
	      return err;
	    }
	}
      else
	{
	  /* There are problematic nodes, re-calculate incrementally.  */
	  err = check_arrival_expand_ecl_sub (dfa, &new_nodes, cur_node,
					      ex_subexp, type);
	  if (BE (err != REG_NOERROR, 0))
	    {
	      re_node_set_free (&new_nodes);
	      return err;
	    }
	}
    }
  re_node_set_free (cur_nodes);
  *cur_nodes = new_nodes;
  return REG_NOERROR;
}