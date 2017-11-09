static void
internal_function
re_node_set_remove_at (re_node_set *set, int idx)
{
  if (idx < 0 || idx >= set->nelem)
    return;
  --set->nelem;
  for (; idx < set->nelem; idx++)
    set->elems[idx] = set->elems[idx + 1];
}