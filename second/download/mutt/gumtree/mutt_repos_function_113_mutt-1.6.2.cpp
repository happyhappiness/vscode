static int compare_score (const void *a, const void *b)
{
  HEADER **pa = (HEADER **) a;
  HEADER **pb = (HEADER **) b;
  int result = (*pb)->score - (*pa)->score; /* note that this is reverse */
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}