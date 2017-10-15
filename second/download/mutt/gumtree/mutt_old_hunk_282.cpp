static void draw_envelope_addr (int line, ADDRESS *addr)
{
  char buf[LONG_STRING];

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), addr, 1);
  mutt_window_mvprintw (MuttIndexWindow, line, 0, TITLE_FMT, Prompts[line]);
  mutt_paddstr (W, buf);
}

static void draw_envelope (HEADER *msg, char *fcc)
{
  draw_envelope_addr (HDR_FROM, msg->env->from);
  draw_envelope_addr (HDR_TO, msg->env->to);
  draw_envelope_addr (HDR_CC, msg->env->cc);
  draw_envelope_addr (HDR_BCC, msg->env->bcc);
  mutt_window_mvprintw (MuttIndexWindow, HDR_SUBJECT, 0, TITLE_FMT, Prompts[HDR_SUBJECT]);
  mutt_paddstr (W, NONULL (msg->env->subject));
  draw_envelope_addr (HDR_REPLYTO, msg->env->reply_to);
  mutt_window_mvprintw (MuttIndexWindow, HDR_FCC, 0, TITLE_FMT, Prompts[HDR_FCC]);
  mutt_paddstr (W, fcc);

  if (WithCrypto)
    redraw_crypt_lines (msg);

#ifdef MIXMASTER
