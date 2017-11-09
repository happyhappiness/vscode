static void print_fixed_line (const char *line, STATE *s, int ql,
			      flowed_state_t *fst)
{
  print_indent (ql, s, add_quote_suffix (s, ql));
  if (line && *line)
    state_puts (line, s);
  state_putc ('\n', s);

  fst->width = 0;
  fst->spaces = 0;
}