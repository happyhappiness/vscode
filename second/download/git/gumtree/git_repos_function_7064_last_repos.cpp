static reg_errcode_t
internal_function
re_node_set_alloc (re_node_set *set, int size)
{
  /*
   * ADR: valgrind says size can be 0, which then doesn't
   * free the block of size 0.  Harumph. This seems
   * to work ok, though.
   */
  if (size == 0)
    {
       memset(set, 0, sizeof(*set));
       return REG_NOERROR;
    }
  set->alloc = size;
  set->nelem = 0;
  set->elems = re_malloc (int, size);
  if (BE (set->elems == NULL, 0))
    return REG_ESPACE;
  return REG_NOERROR;
}