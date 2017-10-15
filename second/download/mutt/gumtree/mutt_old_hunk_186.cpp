      addstr (_(" (S/MIME)"));
  }

  if (option (OPTCRYPTOPPORTUNISTICENCRYPT) && (msg->security & OPPENCRYPT))
      addstr (_(" (OppEnc mode)"));

  clrtoeol ();
  move (HDR_CRYPTINFO, 0);
  clrtoeol ();

  if ((WithCrypto & APPLICATION_PGP)
      && (msg->security & APPLICATION_PGP) && (msg->security & SIGN))
    printw ("%s%s", _(" sign as: "), PgpSignAs ? PgpSignAs : _("<default>"));

  if ((WithCrypto & APPLICATION_SMIME)
      && (msg->security & APPLICATION_SMIME) && (msg->security & SIGN)) {
      printw ("%s%s", _(" sign as: "), SmimeDefaultKey ? SmimeDefaultKey : _("<default>"));
  }

  if ((WithCrypto & APPLICATION_SMIME)
      && (msg->security & APPLICATION_SMIME)
      && (msg->security & ENCRYPT)
      && SmimeCryptAlg
      && *SmimeCryptAlg) {
      mvprintw (HDR_CRYPTINFO, 40, "%s%s", _("Encrypt with: "),
		NONULL(SmimeCryptAlg));
  }
}


#ifdef MIXMASTER

static void redraw_mix_line (LIST *chain)
{
  int c;
  char *t;

  mvaddstr (HDR_MIX, 0,     "     Mix: ");

  if (!chain)
  {
    addstr ("<no chain defined>");
    clrtoeol ();
    return;
  }
  
  for (c = 12; chain; chain = chain->next)
  {
    t = chain->data;
    if (t && t[0] == '0' && t[1] == '\0')
      t = "<random>";
    
    if (c + mutt_strlen (t) + 2 >= COLS)
      break;

    addstr (NONULL(t));
    if (chain->next)
      addstr (", ");

