size_t mutt_wstr_trunc (const char *src, size_t maxlen, size_t maxwid, size_t *width)
{
  wchar_t wc;
  size_t n, w = 0, l = 0, cl;
  int cw;
  mbstate_t mbstate;

  if (!src)
    goto out;

  n = mutt_strlen (src);

  memset (&mbstate, 0, sizeof (mbstate));
  for (w = 0; n && (cl = mbrtowc (&wc, src, n, &mbstate)); src += cl, n -= cl)
  {
    if (cl == (size_t)(-1) || cl == (size_t)(-2))
    {
      if (cl == (size_t)(-1))
        memset (&mbstate, 0, sizeof (mbstate));
      cl = (cl == (size_t)(-1)) ? 1 : n;
      wc = replacement_char ();
    }
    cw = wcwidth (wc);
    /* hack because MUTT_TREE symbols aren't turned into characters
     * until rendered by print_enriched_string (#3364) */
    if (cw < 0 && cl == 1 && src[0] && src[0] < MUTT_TREE_MAX)
      cw = 1;
    else if (cw < 0)
      cw = 0;			/* unprintable wchar */
    if (cl + l > maxlen || cw + w > maxwid)
      break;
    l += cl;
    w += cw;
  }
out:
  if (width)
    *width = w;
  return l;
}