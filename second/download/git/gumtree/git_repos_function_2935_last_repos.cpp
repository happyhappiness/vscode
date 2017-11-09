static inline void
string_list_sort (string_list_ty *slp)
{
  QSORT(slp->item, slp->nitems, cmp_string);
}