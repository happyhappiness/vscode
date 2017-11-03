static void format_line (FILE *f, int ismacro,
			 const char *t1, const char *t2, const char *t3)
{
  int col;
  int col_a, col_b;
  int split;
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
      fputs ("_\010", f);
    fputs ("M ", f);
    col += 2;

    if (!split)
    {
      col += print_macro (f, col_b - col - 4, &t2);
      if (mutt_strwidth (t2) > col_b - col)
	t2 = "...";
    }
  }

  col += print_macro (f, col_b - col - 1, &t2);
  if (split)
    fputc ('\n', f);
  else
    col = pad (f, col, col_b);

  if (split)
  {
    print_macro (f, LONG_STRING, &t3);
    fputc ('\n', f);
  }
  else
  {
    while (*t3)
    {
      n = MuttIndexWindow->cols - col;

      if (ismacro >= 0)
      {
	SKIPWS(t3);
	n = get_wrapped_width (t3, n);
      }

      n = print_macro (f, n, &t3);

      if (*t3)
      {
        if (mutt_strcmp (Pager, "builtin"))
	{
	  fputc ('\n', f);
	  n = 0;
	}
	else
	{
	  n += col - MuttIndexWindow->cols;
	  if (option (OPTMARKERS))
	    ++n;
	}
	col = pad (f, n, col_b);
      }
    }
  }

  fputc ('\n', f);
}