int compare_from (const void *a, const void *b)
{
  HEADER **ppa = (HEADER **) a;
  HEADER **ppb = (HEADER **) b;
  char *fa, *fb;
  int result;

  fa = mutt_get_name ((*ppa)->env->from);
  fb = mutt_get_name ((*ppb)->env->from);
  result = mutt_strcasecmp (fa, fb);
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}