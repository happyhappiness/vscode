static int
internal_function
re_node_set_insert_last (re_node_set *set, int elem)
{
  /* Realloc if we need.  */
  if (set->alloc == set->nelem)
    {
      int *new_elems;
      set->alloc = (set->alloc + 1) * 2;
      new_elems = re_realloc (set->elems, int, set->alloc);
      if (BE (new_elems == NULL, 0))
	return -1;
      set->elems = new_elems;
    }

  /* Insert the new element.  */
  set->elems[set->nelem++] = elem;
  return 1;
}