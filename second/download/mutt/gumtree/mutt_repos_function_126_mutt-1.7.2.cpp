int mutt_which_case (const char *s)
{
  wchar_t w;
  mbstate_t mb;
  size_t l;
  
  memset (&mb, 0, sizeof (mb));
  
  for (; (l = mbrtowc (&w, s, MB_CUR_MAX, &mb)) != 0; s += l)
  {
    if (l == (size_t) -2)
      continue; /* shift sequences */
    if (l == (size_t) -1)
      return 0; /* error; assume case-sensitive */
    if (iswalpha ((wint_t) w) && iswupper ((wint_t) w))
      return 0; /* case-sensitive */
  }

  return REG_ICASE; /* case-insensitive */
}