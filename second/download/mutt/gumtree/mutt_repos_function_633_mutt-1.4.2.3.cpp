static void flowed_quote (STATE *s, int level)
{
  int i;
  
  if (s->prefix)
  {
    if (option (OPTTEXTFLOWED))
      level++;
    else
      state_puts (s->prefix, s);
  }
  
  for (i = 0; i < level; i++)
    state_putc ('>', s);
}