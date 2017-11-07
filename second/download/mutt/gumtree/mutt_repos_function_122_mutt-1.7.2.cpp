static int compare_spam (const void *a, const void *b)
{
  HEADER **ppa = (HEADER **) a;
  HEADER **ppb = (HEADER **) b;
  char   *aptr, *bptr;
  int     ahas, bhas;
  int     result = 0;
  double  difference;

  /* Firstly, require spam attributes for both msgs */
  /* to compare. Determine which msgs have one.     */
  ahas = (*ppa)->env && (*ppa)->env->spam;
  bhas = (*ppb)->env && (*ppb)->env->spam;

  /* If one msg has spam attr but other does not, sort the one with first. */
  if (ahas && !bhas)
    return (SORTCODE(1));
  if (!ahas && bhas)
    return (SORTCODE(-1));

  /* Else, if neither has a spam attr, presume equality. Fall back on aux. */
  if (!ahas && !bhas)
  {
    AUXSORT(result, a, b);
    return (SORTCODE(result));
  }


  /* Both have spam attrs. */

  /* preliminary numeric examination */
  difference = (strtod((*ppa)->env->spam->data, &aptr) -
                strtod((*ppb)->env->spam->data, &bptr));

  /* map double into comparison (-1, 0, or 1) */
  result = (difference < 0.0 ? -1 : difference > 0.0 ? 1 : 0);

  /* If either aptr or bptr is equal to data, there is no numeric    */
  /* value for that spam attribute. In this case, compare lexically. */
  if ((aptr == (*ppa)->env->spam->data) || (bptr == (*ppb)->env->spam->data))
    return (SORTCODE(strcmp(aptr, bptr)));

  /* Otherwise, we have numeric value for both attrs. If these values */
  /* are equal, then we first fall back upon string comparison, then  */
  /* upon auxiliary sort.                                             */
  if (result == 0)
  {
    result = strcmp(aptr, bptr);
    if (result == 0)
      AUXSORT(result, a, b);
  }

  return (SORTCODE(result));
}