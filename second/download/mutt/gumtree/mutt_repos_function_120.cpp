static int compare_date_received (const void *a, const void *b)
{
  HEADER **pa = (HEADER **) a;
  HEADER **pb = (HEADER **) b;
  int result = (*pa)->received - (*pb)->received;
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}