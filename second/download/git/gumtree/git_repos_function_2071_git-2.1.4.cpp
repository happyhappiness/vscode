static inline void
string_list_append (string_list_ty *slp, const char *s)
{
  /* Grow the list.  */
  if (slp->nitems >= slp->nitems_max)
    {
      size_t nbytes;

      slp->nitems_max = slp->nitems_max * 2 + 4;
      nbytes = slp->nitems_max * sizeof (slp->item[0]);
      slp->item = (const char **) xrealloc (slp->item, nbytes);
    }

  /* Add the string to the end of the list.  */
  slp->item[slp->nitems++] = s;
}