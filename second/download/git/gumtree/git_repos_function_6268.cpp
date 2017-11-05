static int
internal_function
re_node_set_insert (re_node_set *set, int elem)
{
  int idx;
  /* In case the set is empty.  */
  if (set->alloc == 0)
    {
      if (BE (re_node_set_init_1 (set, elem) == REG_NOERROR, 1))
	return 1;
      else
	return -1;
    }

  if (BE (set->nelem, 0) == 0)
    {
      /* We already guaranteed above that set->alloc != 0.  */
      set->elems[0] = elem;
      ++set->nelem;
      return 1;
    }

  /* Realloc if we need.  */
  if (set->alloc == set->nelem)
    {
      int *new_elems;
      set->alloc = set->alloc * 2;
      new_elems = re_realloc (set->elems, int, set->alloc);
      if (BE (new_elems == NULL, 0))
	return -1;
      set->elems = new_elems;
    }

  /* Move the elements which follows the new element.  Test the
     first element separately to skip a check in the inner loop.  */
  if (elem < set->elems[0])
    {
      idx = 0;
      for (idx = set->nelem; idx > 0; idx--)
	set->elems[idx] = set->elems[idx - 1];
    }
  else
    {
      for (idx = set->nelem; set->elems[idx - 1] > elem; idx--)
	set->elems[idx] = set->elems[idx - 1];
    }

  /* Insert the new element.  */
  set->elems[idx] = elem;
  ++set->nelem;
  return 1;
}