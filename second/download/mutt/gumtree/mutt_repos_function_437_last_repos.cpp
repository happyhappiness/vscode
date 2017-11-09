int smime_send_menu (HEADER *msg)
{
  smime_key_t *key;
  char *prompt, *letters, *choices;
  int choice;

  if (!(WithCrypto & APPLICATION_SMIME))
    return msg->security;

  msg->security |= APPLICATION_SMIME;

  /*
   * Opportunistic encrypt is controlling encryption.
   * NOTE: "Signing" and "Clearing" only adjust the sign bit, so we have different
   *       letter choices for those.
   */
  if (option (OPTCRYPTOPPORTUNISTICENCRYPT) && (msg->security & OPPENCRYPT))
  {
    prompt = _("S/MIME (s)ign, encrypt (w)ith, sign (a)s, (c)lear, or (o)ppenc mode off? ");
    /* L10N: The 'f' is from "forget it", an old undocumented synonym of
       'clear'.  Please use a corresponding letter in your language.
       Alternatively, you may duplicate the letter 'c' is translated to.
       This comment also applies to the two following letter sequences. */
    letters = _("swafco");
    choices = "SwaFCo";
  }
  /*
   * Opportunistic encryption option is set, but is toggled off
   * for this message.
   */
  else if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
  {
    prompt = _("S/MIME (e)ncrypt, (s)ign, encrypt (w)ith, sign (a)s, (b)oth, (c)lear, or (o)ppenc mode? ");
    letters = _("eswabfco");
    choices = "eswabfcO";
  }
  /*
   * Opportunistic encryption is unset
   */
  else
  {
    prompt = _("S/MIME (e)ncrypt, (s)ign, encrypt (w)ith, sign (a)s, (b)oth, or (c)lear? ");
    letters = _("eswabfc");
    choices = "eswabfc";
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

    case 'w': /* encrypt (w)ith */
      {
        msg->security |= ENCRYPT;
        do
        {
          /* I use "dra" because "123" is recognized anyway */
          switch (mutt_multi_choice (_("Choose algorithm family:"
                                      " 1: DES, 2: RC2, 3: AES,"
                                      " or (c)lear? "),
                                    _("drac")))
          {
          case 1:
            switch (choice = mutt_multi_choice (_("1: DES, 2: Triple-DES "),
                                                _("dt")))
            {
            case 1:
              mutt_str_replace (&SmimeCryptAlg, "des");
              break;
            case 2:
              mutt_str_replace (&SmimeCryptAlg, "des3");
              break;
            }
            break;

          case 2:
            switch (choice = mutt_multi_choice (_("1: RC2-40, 2: RC2-64, 3: RC2-128 "),
                                                _("468")))
            {
            case 1:
              mutt_str_replace (&SmimeCryptAlg, "rc2-40");
              break;
            case 2:
              mutt_str_replace (&SmimeCryptAlg, "rc2-64");
              break;
            case 3:
              mutt_str_replace (&SmimeCryptAlg, "rc2-128");
              break;
            }
            break;

          case 3:
            switch (choice = mutt_multi_choice (_("1: AES128, 2: AES192, 3: AES256 "),
                                                _("895")))
            {
            case 1:
              mutt_str_replace (&SmimeCryptAlg, "aes128");
              break;
            case 2:
              mutt_str_replace (&SmimeCryptAlg, "aes192");
              break;
            case 3:
              mutt_str_replace (&SmimeCryptAlg, "aes256");
              break;
            }
            break;

          case 4: /* (c)lear */
            FREE (&SmimeCryptAlg);
            /* fallback */
          case -1: /* Ctrl-G or Enter */
            choice = 0;
            break;
          }
        } while (choice == -1);
      }
      break;

    case 's': /* (s)ign */
    case 'S': /* (s)ign in oppenc mode */
      if(!SmimeDefaultKey)
      {
        if ((key = smime_ask_for_key (_("Sign as: "), KEYFLAG_CANSIGN, 0)))
        {
          mutt_str_replace (&SmimeDefaultKey, key->hash);
          smime_free_key (&key);
        }
        else
          break;
      }
      if (choices[choice - 1] == 's')
        msg->security &= ~ENCRYPT;
      msg->security |= SIGN;
      break;

    case 'a': /* sign (a)s */

      if ((key = smime_ask_for_key (_("Sign as: "), KEYFLAG_CANSIGN, 0))) 
      {
        mutt_str_replace (&SmimeDefaultKey, key->hash);
        smime_free_key (&key);
          
        msg->security |= SIGN;

        /* probably need a different passphrase */
        crypt_smime_void_passphrase ();
      }

      break;

    case 'b': /* (b)oth */
      msg->security |= (ENCRYPT | SIGN);
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