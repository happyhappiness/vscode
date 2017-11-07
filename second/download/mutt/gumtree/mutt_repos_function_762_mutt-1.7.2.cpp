static int gpgme_send_menu (HEADER *msg, int *redraw, int is_smime)
{
  crypt_key_t *p;
  char input_signas[SHORT_STRING];
  char *prompt, *letters, *choices;
  int choice;

  if (is_smime)
    msg->security |= APPLICATION_SMIME;
  else
    msg->security |= APPLICATION_PGP;

  /*
   * Opportunistic encrypt is controlling encryption.
   * NOTE: "Signing" and "Clearing" only adjust the sign bit, so we have different
   *       letter choices for those.
   */
  if (option (OPTCRYPTOPPORTUNISTICENCRYPT) && (msg->security & OPPENCRYPT))
  {
    if (is_smime)
    {
      prompt = _("S/MIME (s)ign, sign (a)s, (p)gp, (c)lear, or (o)ppenc mode off? ");
      /* L10N: The 'f' is from "forget it", an old undocumented synonym of
         'clear'.  Please use a corresponding letter in your language.
         Alternatively, you may duplicate the letter 'c' is translated to.
         This comment also applies to the five following letter sequences. */
      letters = _("sapfco");
      choices = "SapFCo";
    }
    else
    {
      prompt = _("PGP (s)ign, sign (a)s, s/(m)ime, (c)lear, or (o)ppenc mode off? ");
      letters = _("samfco");
      choices = "SamFCo";
    }
  }
  /*
   * Opportunistic encryption option is set, but is toggled off
   * for this message.
   */
  else if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
  {
    if (is_smime)
    {
      prompt = _("S/MIME (e)ncrypt, (s)ign, sign (a)s, (b)oth, (p)gp, (c)lear, or (o)ppenc mode? ");
      letters = _("esabpfco");
      choices = "esabpfcO";
    }
    else
    {
      prompt = _("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, s/(m)ime, (c)lear, or (o)ppenc mode? ");
      letters = _("esabmfco");
      choices = "esabmfcO";
    }
  }
  /*
   * Opportunistic encryption is unset
   */
  else
  {
    if (is_smime)
    {
      prompt = _("S/MIME (e)ncrypt, (s)ign, sign (a)s, (b)oth, (p)gp or (c)lear? ");
      letters = _("esabpfc");
      choices = "esabpfc";
    }
    else
    {
      prompt = _("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, s/(m)ime or (c)lear? ");
      letters = _("esabmfc");
      choices = "esabmfc";
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
      if ((p = crypt_ask_for_key (_("Sign as: "), NULL, KEYFLAG_CANSIGN,
                                  is_smime? APPLICATION_SMIME:APPLICATION_PGP,
                                  NULL)))
      {
        snprintf (input_signas, sizeof (input_signas), "0x%s",
            crypt_fpr_or_lkeyid (p));
        mutt_str_replace (is_smime? &SmimeDefaultKey : &PgpSignAs, input_signas);
        crypt_free_key (&p); 

        msg->security |= SIGN;
      }
      *redraw = REDRAW_FULL;
      break;

    case 'b': /* (b)oth */
      msg->security |= (ENCRYPT | SIGN);
      break;

    case 'p': /* (p)gp or s/(m)ime */
    case 'm':
      is_smime = !is_smime;
      if (is_smime)
      {
        msg->security &= ~APPLICATION_PGP;
        msg->security |= APPLICATION_SMIME;
      }
      else
      {
        msg->security &= ~APPLICATION_SMIME;
        msg->security |= APPLICATION_PGP;
      }
      crypt_opportunistic_encrypt (msg);
      break;

    case 'f': /* (f)orget it: kept for backward compatibility. */
    case 'c': /* (c)lear */
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
    }
  }

  return (msg->security);
}