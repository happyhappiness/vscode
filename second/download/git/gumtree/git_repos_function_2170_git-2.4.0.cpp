static inline void
string_list_append (string_list_ty *slp, const char *s)
{
  /* Grow the list.  */
  if (slp->nitems >= slp->nitems_max)
    {
      slp->nitems_max = slp->nitems_max * 2 + 4;
      REALLOC_ARRAY(slp->item, slp->nitems_max);
    }

  /* Add the string to the end of the list.  */
  slp->item[slp->nitems++] = s;
}