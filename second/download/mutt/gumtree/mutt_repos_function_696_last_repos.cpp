struct hash_elem *hash_walk(const HASH *table, struct hash_walk_state *state)
{
  if (state->last && state->last->next)
  {
    state->last = state->last->next;
    return state->last;
  }

  if (state->last)
    state->index++;

  while (state->index < table->nelem)
  {
    if (table->table[state->index])
    {
      state->last = table->table[state->index];
      return state->last;
    }
    state->index++;
  } 

  state->index = 0;
  state->last = NULL;
  return NULL;
}