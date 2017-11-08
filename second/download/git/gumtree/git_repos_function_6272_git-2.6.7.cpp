static inline unsigned int
internal_function
calc_state_hash (const re_node_set *nodes, unsigned int context)
{
  unsigned int hash = nodes->nelem + context;
  int i;
  for (i = 0 ; i < nodes->nelem ; i++)
    hash += nodes->elems[i];
  return hash;
}