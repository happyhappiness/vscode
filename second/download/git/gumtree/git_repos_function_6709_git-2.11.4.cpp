static reg_errcode_t
internal_function
re_node_set_init_union (re_node_set *dest, const re_node_set *src1,
			const re_node_set *src2)
{
  int i1, i2, id;
  if (src1 != NULL && src1->nelem > 0 && src2 != NULL && src2->nelem > 0)
    {
      dest->alloc = src1->nelem + src2->nelem;
      dest->elems = re_malloc (int, dest->alloc);
      if (BE (dest->elems == NULL, 0))
	return REG_ESPACE;
    }
  else
    {
      if (src1 != NULL && src1->nelem > 0)
	return re_node_set_init_copy (dest, src1);
      else if (src2 != NULL && src2->nelem > 0)
	return re_node_set_init_copy (dest, src2);
      else
	re_node_set_init_empty (dest);
      return REG_NOERROR;
    }
  for (i1 = i2 = id = 0 ; i1 < src1->nelem && i2 < src2->nelem ;)
    {
      if (src1->elems[i1] > src2->elems[i2])
	{
	  dest->elems[id++] = src2->elems[i2++];
	  continue;
	}
      if (src1->elems[i1] == src2->elems[i2])
	++i2;
      dest->elems[id++] = src1->elems[i1++];
    }
  if (i1 < src1->nelem)
    {
      memcpy (dest->elems + id, src1->elems + i1,
	     (src1->nelem - i1) * sizeof (int));
      id += src1->nelem - i1;
    }
  else if (i2 < src2->nelem)
    {
      memcpy (dest->elems + id, src2->elems + i2,
	     (src2->nelem - i2) * sizeof (int));
      id += src2->nelem - i2;
    }
  dest->nelem = id;
  return REG_NOERROR;
}