static reg_errcode_t
register_state (const re_dfa_t *dfa, re_dfastate_t *newstate,
		unsigned int hash)
{
  struct re_state_table_entry *spot;
  reg_errcode_t err;
  int i;

  newstate->hash = hash;
  err = re_node_set_alloc (&newstate->non_eps_nodes, newstate->nodes.nelem);
  if (BE (err != REG_NOERROR, 0))
    return REG_ESPACE;
  for (i = 0; i < newstate->nodes.nelem; i++)
    {
      int elem = newstate->nodes.elems[i];
      if (!IS_EPSILON_NODE (dfa->nodes[elem].type))
	if (re_node_set_insert_last (&newstate->non_eps_nodes, elem) < 0)
	  return REG_ESPACE;
    }

  spot = dfa->state_table + (hash & dfa->state_hash_mask);
  if (BE (spot->alloc <= spot->num, 0))
    {
      int new_alloc = 2 * spot->num + 2;
      re_dfastate_t **new_array = re_realloc (spot->array, re_dfastate_t *,
					      new_alloc);
      if (BE (new_array == NULL, 0))
	return REG_ESPACE;
      spot->array = new_array;
      spot->alloc = new_alloc;
    }
  spot->array[spot->num++] = newstate;
  return REG_NOERROR;
}