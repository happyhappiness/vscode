static int
sorted_string_list_member (const string_list_ty *slp, const char *s)
{
  size_t j1, j2;

  j1 = 0;
  j2 = slp->nitems;
  if (j2 > 0)
    {
      /* Binary search.  */
      while (j2 - j1 > 1)
	{
	  /* Here we know that if s is in the list, it is at an index j
	     with j1 <= j < j2.  */
	  size_t j = (j1 + j2) >> 1;
	  int result = strcmp (slp->item[j], s);

	  if (result > 0)
	    j2 = j;
	  else if (result == 0)
	    return 1;
	  else
	    j1 = j + 1;
	}
      if (j2 > j1)
	if (strcmp (slp->item[j1], s) == 0)
	  return 1;
    }
  return 0;
}