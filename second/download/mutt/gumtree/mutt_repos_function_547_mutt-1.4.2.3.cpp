static int my_addwch (wchar_t wc)
{
  int n = wcwidth (wc);
  if (IsWPrint (wc) && n > 0)
    return mutt_addwch (wc);
  if (!(wc & ~0x7f))
    return printw ("^%c", ((int)wc + 0x40) & 0x7f);
  if (!(wc & ~0xffff))
    return printw ("\\u%04x", (int)wc);
  return printw ("\\u%08x", (int)wc);
}