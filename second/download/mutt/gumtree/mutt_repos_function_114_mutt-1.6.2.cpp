static int compare_size (const void *a, const void *b)
{
  HEADER **pa = (HEADER **) a;
  HEADER **pb = (HEADER **) b;
  int result = (*pa)->content->length - (*pb)->content->length;
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}