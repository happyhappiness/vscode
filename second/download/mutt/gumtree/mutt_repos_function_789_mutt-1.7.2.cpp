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
  redraw_mix_line (msg->chain);
#endif

  SETCOLOR (MT_COLOR_STATUS);
  mutt_window_mvaddstr (MuttIndexWindow, HDR_ATTACH - 1, 0, _("-- Attachments"));
  mutt_window_clrtoeol (MuttIndexWindow);

  NORMAL_COLOR;
}