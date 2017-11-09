static void draw_envelope_addr (int line, ADDRESS *addr)
{
  char buf[LONG_STRING];

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), addr, 1);
  SETCOLOR (MT_COLOR_COMPOSE_HEADER);
  mutt_window_mvprintw (MuttIndexWindow, line, 0,
                        "%*s", HeaderPadding[line], _(Prompts[line]));
  NORMAL_COLOR;
  mutt_paddstr (W, buf);
}