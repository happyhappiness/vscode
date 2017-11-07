static void draw_envelope_addr (int line, ADDRESS *addr)
{
  char buf[STRING];

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), addr);
  mvprintw (line, 0, TITLE_FMT, Prompts[line - 1]);
  mutt_paddstr (W, buf);
}