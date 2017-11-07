static int my_wcwidth (wchar_t wc)
{
  int n = wcwidth (wc);
  if (IsWPrint (wc) && n > 0)
    return n;
  if (!(wc & ~0x7f))
    return 2;
  if (!(wc & ~0xffff))
    return 6;
  return 10;
}