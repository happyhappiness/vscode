int compare_label (const void *a, const void *b)
{
  HEADER **ppa = (HEADER **) a;
  HEADER **ppb = (HEADER **) b;
  int     ahas, bhas, result = 0;

  /* As with compare_spam, not all messages will have the x-label
   * property.  Blank X-Labels are treated as null in the index
   * display, so we'll consider them as null for sort, too.       */
  ahas = (*ppa)->env && (*ppa)->env->x_label && *((*ppa)->env->x_label);
  bhas = (*ppb)->env && (*ppb)->env->x_label && *((*ppb)->env->x_label);

  /* First we bias toward a message with a label, if the other does not. */
  if (ahas && !bhas)
    return (SORTCODE(-1));
  if (!ahas && bhas)
    return (SORTCODE(1));

  /* If neither has a label, use aux sort. */
  if (!ahas && !bhas)
  {
    AUXSORT(result, a, b);
    return (SORTCODE(result));
  }

  /* If both have a label, we just do a lexical compare. */
  result = mutt_strcasecmp((*ppa)->env->x_label, (*ppb)->env->x_label);
  return (SORTCODE(result));
}