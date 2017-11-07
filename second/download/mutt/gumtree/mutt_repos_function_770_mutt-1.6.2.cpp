static void draw_envelope (HEADER *msg, char *fcc)
{
  draw_envelope_addr (HDR_FROM, msg->env->from);
  draw_envelope_addr (HDR_TO, msg->env->to);
  draw_envelope_addr (HDR_CC, msg->env->cc);
  draw_envelope_addr (HDR_BCC, msg->env->bcc);
  mvprintw (HDR_SUBJECT, 0, TITLE_FMT, Prompts[HDR_SUBJECT - 1]);
  mutt_paddstr (W, NONULL (msg->env->subject));
  draw_envelope_addr (HDR_REPLYTO, msg->env->reply_to);
  mvprintw (HDR_FCC, 0, TITLE_FMT, Prompts[HDR_FCC - 1]);
  mutt_paddstr (W, fcc);

  if (WithCrypto)
    redraw_crypt_lines (msg);

#ifdef MIXMASTER
  redraw_mix_line (msg->chain);
#endif

  SETCOLOR (MT_COLOR_STATUS);
  mvaddstr (HDR_ATTACH - 1, 0, _("-- Attachments"));
  clrtoeol ();

  NORMAL_COLOR;
}