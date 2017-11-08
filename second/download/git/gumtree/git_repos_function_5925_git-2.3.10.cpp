static reg_errcode_t
internal_function
re_node_set_merge (re_node_set *dest, const re_node_set *src)
{
  int is, id, sbase, delta;
  if (src == NULL || src->nelem == 0)
    return REG_NOERROR;
  if (dest->alloc < 2 * src->nelem + dest->nelem)
    {
      int new_alloc = 2 * (src->nelem + dest->alloc);
      int *new_buffer = re_realloc (dest->elems, int, new_alloc);
      if (BE (new_buffer == NULL, 0))
	return REG_ESPACE;
      dest->elems = new_buffer;
      dest->alloc = new_alloc;
    }

  if (BE (dest->nelem == 0, 0))
    {
      dest->nelem = src->nelem;
      memcpy (dest->elems, src->elems, src->nelem * sizeof (int));
      return REG_NOERROR;
    }

  /* Copy into the top of DEST the items of SRC that are not
     found in DEST.  Maybe we could binary search in DEST?  */
  for (sbase = dest->nelem + 2 * src->nelem,
       is = src->nelem - 1, id = dest->nelem - 1; is >= 0 && id >= 0; )
    {
      if (dest->elems[id] == src->elems[is])
	is--, id--;
      else if (dest->elems[id] < src->elems[is])
	dest->elems[--sbase] = src->elems[is--];
      else /* if (dest->elems[id] > src->elems[is]) */
	--id;
    }

  if (is >= 0)
    {
      /* If DEST is exhausted, the remaining items of SRC must be unique.  */
      sbase -= is + 1;
      memcpy (dest->elems + sbase, src->elems, (is + 1) * sizeof (int));
    }

  id = dest->nelem - 1;
  is = dest->nelem + 2 * src->nelem - 1;
  delta = is - sbase + 1;
  if (delta == 0)
    return REG_NOERROR;

  /* Now copy.  When DELTA becomes zero, the remaining
     DEST elements are already in place.  */
  dest->nelem += delta;
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
	    {
	      /* Copy remaining SRC elements.  */
	      memcpy (dest->elems, dest->elems + sbase,
		      delta * sizeof (int));
	      break;
	    }
	}
    }

  return REG_NOERROR;
}