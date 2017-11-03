static int my_wcswidth (const wchar_t *s, size_t n)
{
  int w = 0;
  while (n--)
    w += my_wcwidth (*s++);
  return w;
}