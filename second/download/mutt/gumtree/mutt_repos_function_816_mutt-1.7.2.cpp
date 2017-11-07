void ci_start_color (void)
{
  memset (ColorDefs, A_NORMAL, sizeof (int) * MT_COLOR_MAX);
  ColorQuote = (int *) safe_malloc (COLOR_QUOTE_INIT * sizeof (int));
  memset (ColorQuote, A_NORMAL, sizeof (int) * COLOR_QUOTE_INIT);
  ColorQuoteSize = COLOR_QUOTE_INIT;
  ColorQuoteUsed = 0;

  /* set some defaults */
  ColorDefs[MT_COLOR_STATUS] = A_REVERSE;
  ColorDefs[MT_COLOR_INDICATOR] = A_REVERSE;
  ColorDefs[MT_COLOR_SEARCH] = A_REVERSE;
  ColorDefs[MT_COLOR_MARKERS] = A_REVERSE;
#ifdef USE_SIDEBAR
  ColorDefs[MT_COLOR_HIGHLIGHT] = A_UNDERLINE;
#endif
  /* special meaning: toggle the relevant attribute */
  ColorDefs[MT_COLOR_BOLD] = 0;
  ColorDefs[MT_COLOR_UNDERLINE] = 0;

#ifdef HAVE_COLOR
  start_color ();
#endif
}