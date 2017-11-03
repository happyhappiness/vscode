void state_attach_puts (const char *t, STATE *s)
{
  if (*t != '\n') state_mark_attach (s);
  while (*t)
  {
    state_putc (*t, s);
    if (*t++ == '\n' && *t)
      if (*t != '\n') state_mark_attach (s);
  }
}