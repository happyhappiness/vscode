static int compare_to (const void *a, const void *b)
{
  HEADER **ppa = (HEADER **) a;
  HEADER **ppb = (HEADER **) b;
  char fa[SHORT_STRING];
  const char *fb;
  int result;

  strfcpy (fa, mutt_get_name ((*ppa)->env->to), SHORT_STRING);
  fb = mutt_get_name ((*ppb)->env->to);
  result = mutt_strncasecmp (fa, fb, SHORT_STRING);
  AUXSORT(result,a,b);
  return (SORTCODE (result));
}