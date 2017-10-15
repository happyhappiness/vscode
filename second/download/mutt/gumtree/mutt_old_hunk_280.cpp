  mutt_window_clrtoeol (MuttIndexWindow);
  mutt_window_move (MuttIndexWindow, HDR_CRYPTINFO, 0);
  mutt_window_clrtoeol (MuttIndexWindow);

  if ((WithCrypto & APPLICATION_PGP)
      && (msg->security & APPLICATION_PGP) && (msg->security & SIGN))
    printw (TITLE_FMT "%s", _("sign as: "), PgpSignAs ? PgpSignAs : _("<default>"));

  if ((WithCrypto & APPLICATION_SMIME)
      && (msg->security & APPLICATION_SMIME) && (msg->security & SIGN)) {
      printw (TITLE_FMT "%s", _("sign as: "), SmimeDefaultKey ? SmimeDefaultKey : _("<default>"));
  }

  if ((WithCrypto & APPLICATION_SMIME)
      && (msg->security & APPLICATION_SMIME)
      && (msg->security & ENCRYPT)
      && SmimeCryptAlg
      && *SmimeCryptAlg) {
    mutt_window_mvprintw (MuttIndexWindow, HDR_CRYPTINFO, 40, "%s%s", _("Encrypt with: "),
		NONULL(SmimeCryptAlg));
  }
}


#ifdef MIXMASTER

static void redraw_mix_line (LIST *chain)
{
  int c;
  char *t;

  /* L10N: "Mix" refers to the MixMaster chain for anonymous email */
  mutt_window_mvprintw (MuttIndexWindow, HDR_MIX, 0, TITLE_FMT, _("Mix: "));

  if (!chain)
  {
    addstr ("<no chain defined>");
    mutt_window_clrtoeol (MuttIndexWindow);
    return;
