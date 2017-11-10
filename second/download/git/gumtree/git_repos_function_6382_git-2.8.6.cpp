static re_dfastate_t *
internal_function
re_acquire_state_context (reg_errcode_t *err, const re_dfa_t *dfa,
			  const re_node_set *nodes, unsigned int context)
{
  unsigned int hash;
  re_dfastate_t *new_state;
  struct re_state_table_entry *spot;
  int i;
  if (nodes->nelem == 0)
    {
      *err = REG_NOERROR;
      return NULL;
    }
  hash = calc_state_hash (nodes, context);
  spot = dfa->state_table + (hash & dfa->state_hash_mask);

  for (i = 0 ; i < spot->num ; i++)
    {
      re_dfastate_t *state = spot->array[i];
      if (state->hash == hash
	  && state->context == context
	  && re_node_set_compare (state->entrance_nodes, nodes))
	return state;
    }
  /* There are no appropriate state in `dfa', create the new one.  */
  new_state = create_cd_newstate (dfa, nodes, context, hash);
  if (BE (new_state == NULL, 0))
    *err = REG_ESPACE;

  return new_state;
}