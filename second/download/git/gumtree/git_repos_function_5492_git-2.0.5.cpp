static reg_errcode_t
internal_function
sub_epsilon_src_nodes (const re_dfa_t *dfa, int node, re_node_set *dest_nodes,
		       const re_node_set *candidates)
{
    int ecl_idx;
    reg_errcode_t err;
    re_node_set *inv_eclosure = dfa->inveclosures + node;
    re_node_set except_nodes;
    re_node_set_init_empty (&except_nodes);
    for (ecl_idx = 0; ecl_idx < inv_eclosure->nelem; ++ecl_idx)
      {
	int cur_node = inv_eclosure->elems[ecl_idx];
	if (cur_node == node)
	  continue;
	if (IS_EPSILON_NODE (dfa->nodes[cur_node].type))
	  {
	    int edst1 = dfa->edests[cur_node].elems[0];
	    int edst2 = ((dfa->edests[cur_node].nelem > 1)
			 ? dfa->edests[cur_node].elems[1] : -1);
	    if ((!re_node_set_contains (inv_eclosure, edst1)
		 && re_node_set_contains (dest_nodes, edst1))
		|| (edst2 > 0
		    && !re_node_set_contains (inv_eclosure, edst2)
		    && re_node_set_contains (dest_nodes, edst2)))
	      {
		err = re_node_set_add_intersect (&except_nodes, candidates,
						 dfa->inveclosures + cur_node);
		if (BE (err != REG_NOERROR, 0))
		  {
		    re_node_set_free (&except_nodes);
		    return err;
		  }
	      }
	  }
      }
    for (ecl_idx = 0; ecl_idx < inv_eclosure->nelem; ++ecl_idx)
      {
	int cur_node = inv_eclosure->elems[ecl_idx];
	if (!re_node_set_contains (&except_nodes, cur_node))
	  {
	    int idx = re_node_set_contains (dest_nodes, cur_node) - 1;
	    re_node_set_remove_at (dest_nodes, idx);
	  }
      }
    re_node_set_free (&except_nodes);
    return REG_NOERROR;
}