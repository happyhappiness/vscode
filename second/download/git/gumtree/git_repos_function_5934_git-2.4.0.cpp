static reg_errcode_t
internal_function
re_node_set_add_intersect (re_node_set *dest, const re_node_set *src1,
			   const re_node_set *src2)
{
  int i1, i2, is, id, delta, sbase;
  if (src1->nelem == 0 || src2->nelem == 0)
    return REG_NOERROR;

  /* We need dest->nelem + 2 * elems_in_intersection; this is a
     conservative estimate.  */
  if (src1->nelem + src2->nelem + dest->nelem > dest->alloc)
    {
      int new_alloc = src1->nelem + src2->nelem + dest->alloc;
      int *new_elems = re_realloc (dest->elems, int, new_alloc);
      if (BE (new_elems == NULL, 0))
	return REG_ESPACE;
      dest->elems = new_elems;
      dest->alloc = new_alloc;
    }

  /* Find the items in the intersection of SRC1 and SRC2, and copy
     into the top of DEST those that are not already in DEST itself.  */
  sbase = dest->nelem + src1->nelem + src2->nelem;
  i1 = src1->nelem - 1;
  i2 = src2->nelem - 1;
  id = dest->nelem - 1;
  for (;;)
    {
      if (src1->elems[i1] == src2->elems[i2])
	{
	  /* Try to find the item in DEST.  Maybe we could binary search?  */
	  while (id >= 0 && dest->elems[id] > src1->elems[i1])
	    --id;

	  if (id < 0 || dest->elems[id] != src1->elems[i1])
	    dest->elems[--sbase] = src1->elems[i1];

	  if (--i1 < 0 || --i2 < 0)
	    break;
	}

      /* Lower the highest of the two items.  */
      else if (src1->elems[i1] < src2->elems[i2])
	{
	  if (--i2 < 0)
	    break;
	}
      else
	{
	  if (--i1 < 0)
	    break;
	}
    }

  id = dest->nelem - 1;
  is = dest->nelem + src1->nelem + src2->nelem - 1;
  delta = is - sbase + 1;

  /* Now copy.  When DELTA becomes zero, the remaining
     DEST elements are already in place; this is more or
     less the same loop that is in re_node_set_merge.  */
  dest->nelem += delta;
  if (delta > 0 && id >= 0)
    for (;;)
      {
	if (dest->elems[is] > dest->elems[id])
	  {
	    /* Copy from the top.  */
	    dest->elems[id + delta--] = dest->elems[is--];
	    if (delta == 0)
	      break;
	  }
	else
	  {
	    /* Slide from the bottom.  */
	    dest->elems[id + delta] = dest->elems[id];
	    if (--id < 0)
	      break;
	  }
      }

  /* Copy remaining SRC elements.  */
  memcpy (dest->elems, dest->elems + sbase, delta * sizeof (int));

  return REG_NOERROR;
}