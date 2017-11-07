int mutt_filter_unprintable (char **s)
{
  BUFFER *b = NULL;
  wchar_t wc;
  size_t k, k2;
  char scratch[MB_LEN_MAX + 1];
  char *p = *s;
  mbstate_t mbstate1, mbstate2;

  if (!(b = mutt_buffer_new ()))
    return -1;
  memset (&mbstate1, 0, sizeof (mbstate1));
  memset (&mbstate2, 0, sizeof (mbstate2));
  for (; (k = mbrtowc (&wc, p, MB_LEN_MAX, &mbstate1)); p += k)
  {
    if (k == (size_t)(-1) || k == (size_t)(-2))
    {
      k = 1;
      memset (&mbstate1, 0, sizeof (mbstate1));
      wc = replacement_char();
    }
    if (!IsWPrint (wc))
      wc = '?';
    /* HACK:
     * Work around a gnu screen bug. See ticket #3827.
     * Filter out the RIGHT-TO-LEFT and LEFT-TO-RIGHT bidi marks because
     * they result in screen corruption.
     */
    else if (Charset_is_utf8 &&
             ((wc == (wchar_t)0x200f) || (wc == (wchar_t)0x200e)))
      wc = '?';
    k2 = wcrtomb (scratch, wc, &mbstate2);
    scratch[k2] = '\0';
    mutt_buffer_addstr (b, scratch);
  }
  FREE (s);  /* __FREE_CHECKED__ */
  *s = b->data ? b->data : safe_calloc (1, 1);
  FREE (&b);
  return 0;
}