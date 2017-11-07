static size_t width_ceiling (const wchar_t *s, size_t n, int w1)
{
  const wchar_t *s0 = s;
  int w = 0;
  for (; n; s++, n--)
    if ((w += my_wcwidth (*s)) > w1)
      break;
  return s - s0;  
}