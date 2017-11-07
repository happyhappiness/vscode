static int quote_width (STATE *s, int ql)
{
  int width = mutt_window_wrap_cols (MuttIndexWindow, ReflowWrap);
  if (option(OPTTEXTFLOWED) && (s->flags & MUTT_REPLYING))
  {
    /* When replying, force a wrap at FLOWED_MAX to comply with RFC3676
     * guidelines */
    if (width > FLOWED_MAX)
      width = FLOWED_MAX;
    ++ql; /* When replying, we will add an additional quote level */
  }
  /* adjust the paragraph width subtracting the number of prefix chars */
  width -= space_quotes (s) ? ql*2 : ql;
  /* When displaying (not replying), there may be a space between the prefix
   * string and the paragraph */
  if (add_quote_suffix (s, ql))
    --width;
  /* failsafe for really long quotes */
  if (width <= 0)
    width = FLOWED_MAX; /* arbitrary, since the line will wrap */
  return width;
}