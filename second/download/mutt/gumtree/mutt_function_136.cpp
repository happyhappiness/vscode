static void redraw_crypt_lines (HEADER *msg)
{
  mutt_window_mvprintw (MuttIndexWindow, HDR_CRYPT, 0, TITLE_FMT, "Security: ");

  if ((WithCrypto & (APPLICATION_PGP | APPLICATION_SMIME)) == 0)
  {
    addstr(_("Not supported"));
    return;
  }

  if ((msg->security & (ENCRYPT | SIGN)) == (ENCRYPT | SIGN))
    addstr (_("Sign, Encrypt"));
  else if (msg->security & ENCRYPT)
    addstr (_("Encrypt"));
  else if (msg->security & SIGN)
    addstr (_("Sign"));
  else
    addstr (_("None"));

  if ((msg->security & (ENCRYPT | SIGN)))
  {
    if ((WithCrypto & APPLICATION_PGP) && (msg->security & APPLICATION_PGP))
    {
      if ((msg->security & INLINE))
        addstr (_(" (inline PGP)"));
      else
        addstr (_(" (PGP/MIME)"));
    }
    else if ((WithCrypto & APPLICATION_SMIME) &&
             (msg->security & APPLICATION_SMIME))
      addstr (_(" (S/MIME)"));
  }

  if (option (OPTCRYPTOPPORTUNISTICENCRYPT) && (msg->security & OPPENCRYPT))
      addstr (_(" (OppEnc mode)"));

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