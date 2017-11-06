static size_t print_indent (int ql, STATE *s, int add_suffix)
{
  int i;
  size_t wid = 0;

  if (s->prefix)
  {
    /* use given prefix only for format=fixed replies to format=flowed,
     * for format=flowed replies to format=flowed, use '>' indentation
     */
    if (option (OPTTEXTFLOWED))
      ql++;
    else
    {
      state_puts (s->prefix, s);
      wid = mutt_strwidth (s->prefix);
    }
  }
  for (i = 0; i < ql; i++)
  {
    state_putc ('>', s);
    if (space_quotes (s) )
      state_putc (' ', s);
  }
  if (add_suffix)
    state_putc (' ', s);

  if (space_quotes (s))
    ql *= 2;

  return ql + add_suffix + wid;
}