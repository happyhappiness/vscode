void state_prefix_putc (char c, STATE *s)
{
  if (s->flags & MUTT_PENDINGPREFIX)
  {
    state_reset_prefix (s);
    if (s->prefix)
      state_puts (s->prefix, s);
  }

  state_putc (c, s);

  if (c == '\n')
    state_set_prefix (s);
}