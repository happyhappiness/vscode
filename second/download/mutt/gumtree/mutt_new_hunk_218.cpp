  int n;

  fputs (t1, f);

  /* don't try to press string into one line with less than 40 characters.
     The double parenthesis avoids a gcc warning, sigh ... */
  if ((split = MuttIndexWindow->cols < 40))
  {
    col_a = col = 0;
    col_b = LONG_STRING;
    fputc ('\n', f);
  }
  else
  {
    col_a = MuttIndexWindow->cols > 83 ? (MuttIndexWindow->cols - 32) >> 2 : 12;
    col_b = MuttIndexWindow->cols > 49 ? (MuttIndexWindow->cols - 10) >> 1 : 19;
    col = pad (f, mutt_strwidth(t1), col_a);
  }

  if (ismacro > 0)
  {
    if (!mutt_strcmp (Pager, "builtin"))
