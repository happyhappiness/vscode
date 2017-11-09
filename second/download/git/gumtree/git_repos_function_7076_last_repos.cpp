static re_dfastate_t *
internal_function
re_acquire_state (reg_errcode_t *err, const re_dfa_t *dfa,
		  const re_node_set *nodes)
{
  unsigned int hash;
  re_dfastate_t *new_state;
  struct re_state_table_entry *spot;
  int i;
  if (BE (nodes->nelem == 0, 0))
    {
      *err = REG_NOERROR;
      return NULL;
    }
  hash = calc_state_hash (nodes, 0);
  spot = dfa->state_table + (hash & dfa->state_hash_mask);

  for (i = 0 ; i < spot->num ; i++)
    {
      re_dfastate_t *state = spot->array[i];
      if (hash != state->hash)
	continue;
      if (re_node_set_compare (&state->nodes, nodes))
	return state;
    }

  /* There are no appropriate state in the dfa, create the new one.  */
  new_state = create_ci_newstate (dfa, nodes, hash);
  if (BE (new_state == NULL, 0))
    *err = REG_ESPACE;

  return new_state;
}