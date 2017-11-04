static void redraw_crypt_lines (HEADER *msg)
{
  SETCOLOR (MT_COLOR_COMPOSE_HEADER);
  mutt_window_mvprintw (MuttIndexWindow, HDR_CRYPT, 0,
                        "%*s", HeaderPadding[HDR_CRYPT], _(Prompts[HDR_CRYPT]));
  NORMAL_COLOR;

  if ((WithCrypto & (APPLICATION_PGP | APPLICATION_SMIME)) == 0)
  {
    addstr(_("Not supported"));
    return;
  }

  if ((msg->security & (ENCRYPT | SIGN)) == (ENCRYPT | SIGN))
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_BOTH);
    addstr (_("Sign, Encrypt"));
  }
  else if (msg->security & ENCRYPT)
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_ENCRYPT);
    addstr (_("Encrypt"));
  }
  else if (msg->security & SIGN)
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_SIGN);
    addstr (_("Sign"));
  }
  else
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_NONE);
    addstr (_("None"));
  }
  NORMAL_COLOR;

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
  {
    SETCOLOR (MT_COLOR_COMPOSE_HEADER);
    printw ("%*s", HeaderPadding[HDR_CRYPTINFO], _(Prompts[HDR_CRYPTINFO]));
    NORMAL_COLOR;
    printw ("%s", PgpSignAs ? PgpSignAs : _("<default>"));
  }

  if ((WithCrypto & APPLICATION_SMIME)
      && (msg->security & APPLICATION_SMIME) && (msg->security & SIGN))
  {
    SETCOLOR (MT_COLOR_COMPOSE_HEADER);
    printw ("%*s", HeaderPadding[HDR_CRYPTINFO], _(Prompts[HDR_CRYPTINFO]));
    NORMAL_COLOR;
    printw ("%s", SmimeDefaultKey ? SmimeDefaultKey : _("<default>"));
  }

  if ((WithCrypto & APPLICATION_SMIME)
      && (msg->security & APPLICATION_SMIME)
      && (msg->security & ENCRYPT)
      && SmimeCryptAlg
      && *SmimeCryptAlg)
  {
    SETCOLOR (MT_COLOR_COMPOSE_HEADER);
    mutt_window_mvprintw (MuttIndexWindow, HDR_CRYPTINFO, 40, "%s", _("Encrypt with: "));
    NORMAL_COLOR;
    printw ("%s", NONULL(SmimeCryptAlg));
  }
}