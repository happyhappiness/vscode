int state_putws (const wchar_t *ws, STATE *s)
{
  const wchar_t *p = ws;

  while (p && *p != L'\0')
  {
    if (state_putwc (*p, s) < 0)
      return -1;
    p++;
  }
  return 0;
}