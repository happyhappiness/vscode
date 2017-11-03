static void flush_par (STATE *s, flowed_state_t *fst)
{
  if (fst->width > 0)
  {
    state_putc ('\n', s);
    fst->width = 0;
  }
  fst->spaces = 0;
}