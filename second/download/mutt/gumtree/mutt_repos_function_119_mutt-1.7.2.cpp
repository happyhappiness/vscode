static int compare_from (const void *a, const void *b)
{
  HEADER **ppa = (HEADER **) a;
  HEADER **ppb = (HEADER **) b;
  char fa[SHORT_STRING];
  const char *fb;
  int result;

  strfcpy (fa, mutt_get_name ((*ppa)->env->from), SHORT_STRING);
  fb = mutt_get_name ((*ppb)->env->from);
  result = mutt_strncasecmp (fa, fb, SHORT_STRING);
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}