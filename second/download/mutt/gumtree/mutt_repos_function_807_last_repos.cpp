static void init_header_padding (void)
{
  static short done = 0;
  int i;

  if (done)
    return;
  done = 1;

  for (i = 0; i <= HDR_CRYPT; i++)
    calc_header_width_padding (i, _(Prompts[i]), 1);

  /* Don't include "Sign as: " in the MaxHeaderWidth calculation.  It
   * doesn't show up by default, and so can make the indentation of
   * the other fields look funny. */
  calc_header_width_padding (HDR_CRYPTINFO, _(Prompts[HDR_CRYPTINFO]), 0);

  for (i = 0; i <= HDR_CRYPTINFO; i++)
  {
    HeaderPadding[i] += MaxHeaderWidth;
    if (HeaderPadding[i] < 0)
      HeaderPadding[i] = 0;
  }
}