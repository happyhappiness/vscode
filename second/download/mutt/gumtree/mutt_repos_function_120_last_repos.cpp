static int compare_order (const void *a, const void *b)
{
  HEADER **ha = (HEADER **) a;
  HEADER **hb = (HEADER **) b;

  /* no need to auxsort because you will never have equality here */
  return (SORTCODE ((*ha)->index - (*hb)->index));
}