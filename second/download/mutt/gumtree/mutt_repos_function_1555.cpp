int wcscasecmp (const wchar_t *a, const wchar_t *b)
{
  const wchar_t *p = a;
  const wchar_t *q = b;
  int i;

  if (!a && !b)
    return 0;
  if (!a && b)
    return -1;
  if (a && !b)
    return 1;

  for ( ; *p || *q; p++, q++)
  {
    if ((i = towlower (*p)) - towlower (*q))
      return i;
  }
  return 0;
}