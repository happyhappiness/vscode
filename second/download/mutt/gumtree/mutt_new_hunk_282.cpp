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

static void draw_envelope (HEADER *msg, char *fcc)
{
  draw_envelope_addr (HDR_FROM, msg->env->from);
  draw_envelope_addr (HDR_TO, msg->env->to);
  draw_envelope_addr (HDR_CC, msg->env->cc);
  draw_envelope_addr (HDR_BCC, msg->env->bcc);

  SETCOLOR (MT_COLOR_COMPOSE_HEADER);
  mutt_window_mvprintw (MuttIndexWindow, HDR_SUBJECT, 0,
                        "%*s", HeaderPadding[HDR_SUBJECT], _(Prompts[HDR_SUBJECT]));
  NORMAL_COLOR;
  mutt_paddstr (W, NONULL (msg->env->subject));

  draw_envelope_addr (HDR_REPLYTO, msg->env->reply_to);

  SETCOLOR (MT_COLOR_COMPOSE_HEADER);
  mutt_window_mvprintw (MuttIndexWindow, HDR_FCC, 0,
                        "%*s", HeaderPadding[HDR_FCC], _(Prompts[HDR_FCC]));
  NORMAL_COLOR;
  mutt_paddstr (W, fcc);

  if (WithCrypto)
    redraw_crypt_lines (msg);

#ifdef MIXMASTER
