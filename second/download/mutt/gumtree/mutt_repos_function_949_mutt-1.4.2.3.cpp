void state_attach_puts (const char *t, STATE *s)
{
  state_mark_attach (s);
  while (*t)
  {
    state_putc (*t, s);
    if (*t++ == '\n' && *t)
      state_mark_attach (s);
  }
}