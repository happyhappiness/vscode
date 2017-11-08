static reg_errcode_t
internal_function
add_epsilon_src_nodes (const re_dfa_t *dfa, re_node_set *dest_nodes,
		       const re_node_set *candidates)
{
  reg_errcode_t err = REG_NOERROR;
  int i;

  re_dfastate_t *state = re_acquire_state (&err, dfa, dest_nodes);
  if (BE (err != REG_NOERROR, 0))
    return err;

  if (!state->inveclosure.alloc)
    {
      err = re_node_set_alloc (&state->inveclosure, dest_nodes->nelem);
      if (BE (err != REG_NOERROR, 0))
	return REG_ESPACE;
      for (i = 0; i < dest_nodes->nelem; i++)
	{
	  err = re_node_set_merge (&state->inveclosure,
				   dfa->inveclosures + dest_nodes->elems[i]);
	  if (BE (err != REG_NOERROR, 0))
	    return REG_ESPACE;
	}
    }
  return re_node_set_add_intersect (dest_nodes, candidates,
				    &state->inveclosure);
}