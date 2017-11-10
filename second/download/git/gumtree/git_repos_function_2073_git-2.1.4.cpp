static inline void
string_list_sort (string_list_ty *slp)
{
  if (slp->nitems > 0)
    qsort (slp->item, slp->nitems, sizeof (slp->item[0]), cmp_string);
}