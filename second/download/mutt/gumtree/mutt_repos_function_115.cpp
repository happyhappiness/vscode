static int compare_date_sent (const void *a, const void *b)
{
  HEADER **pa = (HEADER **) a;
  HEADER **pb = (HEADER **) b;
  int result = (*pa)->date_sent - (*pb)->date_sent;
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}