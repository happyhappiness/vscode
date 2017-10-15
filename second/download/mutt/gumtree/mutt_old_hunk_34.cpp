    fputc ('\n', f);
  }
  else
  {
    col_a = COLS > 83 ? (COLS - 32) >> 2 : 12;
    col_b = COLS > 49 ? (COLS - 10) >> 1 : 19;
    col = pad (f, mutt_strlen(t1), col_a);
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
      if (mutt_strlen (t2) > col_b - col)
	t2 = "...";
    }
  }

  col += print_macro (f, col_b - col - 1, &t2);
  if (split)
