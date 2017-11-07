int pgp_send_menu (HEADER *msg, int *redraw)
{
  pgp_key_t p;
  char input_signas[SHORT_STRING];
  char *prompt, *letters, *choices;
  char promptbuf[LONG_STRING];
  int choice;

  if (!(WithCrypto & APPLICATION_PGP))
    return msg->security;

  /* If autoinline and no crypto options set, then set inline. */
  if (option (OPTPGPAUTOINLINE) && 
      !((msg->security & APPLICATION_PGP) && (msg->security & (SIGN|ENCRYPT))))
    msg->security |= INLINE;

  msg->security |= APPLICATION_PGP;

  /*
   * Opportunistic encrypt is controlling encryption.  Allow to toggle
   * between inline and mime, but not turn encryption on or off.
   * NOTE: "Signing" and "Clearing" only adjust the sign bit, so we have different
   *       letter choices for those.
   */
  if (option (OPTCRYPTOPPORTUNISTICENCRYPT) && (msg->security & OPPENCRYPT))
  {
    if (msg->security & (ENCRYPT | SIGN))
    {
      snprintf (promptbuf, sizeof (promptbuf),
          _("PGP (s)ign, sign (a)s, %s format, (c)lear, or (o)ppenc mode off? "),
          (msg->security & INLINE) ? _("PGP/M(i)ME") : _("(i)nline"));
      prompt = promptbuf;
      /* L10N: The 'f' is from "forget it", an old undocumented synonym of
         'clear'.  Please use a corresponding letter in your language.
         Alternatively, you may duplicate the letter 'c' is translated to.
         This comment also applies to the five following letter sequences. */
      letters = _("safcoi");
      choices = "SaFCoi";
    }
    else
    {
      prompt = _("PGP (s)ign, sign (a)s, (c)lear, or (o)ppenc mode off? ");
      letters = _("safco");
      choices = "SaFCo";
    }
  }
  /*
   * Opportunistic encryption option is set, but is toggled off
   * for this message.
   */
  else if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
  {
    /* When the message is not selected for signing or encryption, the toggle
    * between PGP/MIME and Traditional doesn't make sense.
    */
    if (msg->security & (ENCRYPT | SIGN))
    {

      snprintf (promptbuf, sizeof (promptbuf), 
          _("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, %s format, (c)lear, or (o)ppenc mode? "),
          (msg->security & INLINE) ? _("PGP/M(i)ME") : _("(i)nline"));
      prompt = promptbuf;
      letters = _("esabfcoi");
      choices = "esabfcOi";
    }
    else
    {
      prompt = _("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, (c)lear, or (o)ppenc mode? ");
      letters = _("esabfco");
      choices = "esabfcO";
    }
  }
  /*
   * Opportunistic encryption is unset
   */
  else
  {
    if (msg->security & (ENCRYPT | SIGN))
    {

      snprintf (promptbuf, sizeof (promptbuf), 
          _("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, %s format, or (c)lear? "),
          (msg->security & INLINE) ? _("PGP/M(i)ME") : _("(i)nline"));
      prompt = promptbuf;
      letters = _("esabfci");
      choices = "esabfci";
    }
    else
    {
      prompt = _("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, or (c)lear? ");
      letters = _("esabfc");
      choices = "esabfc";
    }
  }

  choice = mutt_multi_choice (prompt, letters);
  if (choice > 0)
  {
    switch (choices[choice - 1])
    {
    case 'e': /* (e)ncrypt */
      msg->security |= ENCRYPT;
      msg->security &= ~SIGN;
      break;

    case 's': /* (s)ign */
      msg->security &= ~ENCRYPT;
      msg->security |= SIGN;
      break;

    case 'S': /* (s)ign in oppenc mode */
      msg->security |= SIGN;
      break;

    case 'a': /* sign (a)s */
      unset_option(OPTPGPCHECKTRUST);

      if ((p = pgp_ask_for_key (_("Sign as: "), NULL, 0, PGP_SECRING)))
      {
        snprintf (input_signas, sizeof (input_signas), "0x%s",
            pgp_fpr_or_lkeyid (p));
        mutt_str_replace (&PgpSignAs, input_signas);
        pgp_free_key (&p);

        msg->security |= SIGN;

        crypt_pgp_void_passphrase ();  /* probably need a different passphrase */
      }
      *redraw = REDRAW_FULL;
      break;

    case 'b': /* (b)oth */
      msg->security |= (ENCRYPT | SIGN);
      break;

    case 'f': /* (f)orget it: kept for backward compatibility. */
    case 'c': /* (c)lear     */
      msg->security &= ~(ENCRYPT | SIGN);
      break;

    case 'F': /* (f)orget it or (c)lear in oppenc mode */
    case 'C':
      msg->security &= ~SIGN;
      break;

    case 'O': /* oppenc mode on */
      msg->security |= OPPENCRYPT;
      crypt_opportunistic_encrypt (msg);
      break;

    case 'o': /* oppenc mode off */
      msg->security &= ~OPPENCRYPT;
      break;

    case 'i': /* toggle (i)nline */
      msg->security ^= INLINE;
      break;
    }
  }

  return (msg->security);
}