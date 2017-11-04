static void print_key_info (gpgme_key_t key, FILE *fp)
{
  int idx;
  const char *s = NULL, *s2 = NULL;
  time_t tt = 0;
  struct tm *tm;
  char shortbuf[SHORT_STRING];
  unsigned long aval = 0;
  const char *delim;
  int is_pgp = 0;
  int i;
  gpgme_user_id_t uid = NULL;
  static int max_header_width = 0;
  int width;

  if (!max_header_width)
  {
    for (i = 0; i < KIP_END; i++)
    {
      KeyInfoPadding[i] = mutt_strlen (_(KeyInfoPrompts[i]));
      width = mutt_strwidth (_(KeyInfoPrompts[i]));
      if (max_header_width < width)
        max_header_width = width;
      KeyInfoPadding[i] -= width;
    }
    for (i = 0; i < KIP_END; i++)
      KeyInfoPadding[i] += max_header_width;
  }

  is_pgp = key->protocol == GPGME_PROTOCOL_OpenPGP;

  for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
    {
      if (uid->revoked)
        continue;

      s = uid->uid;

      if (!idx)
        fprintf (fp, "%*s", KeyInfoPadding[KIP_NAME], _(KeyInfoPrompts[KIP_NAME]));
      else
        fprintf (fp, "%*s", KeyInfoPadding[KIP_AKA], _(KeyInfoPrompts[KIP_AKA]));
      if (uid->invalid)
        {
          /* L10N: comes after the Name or aka if the key is invalid */
          fputs (_("[Invalid]"), fp);
          putc (' ', fp);
        }
      if (is_pgp)
        print_utf8 (fp, s, strlen(s));
      else
        parse_and_print_user_id (fp, s);
      putc ('\n', fp);
    }

  if (key->subkeys && (key->subkeys->timestamp > 0))
    {
      tt = key->subkeys->timestamp;

      tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
      strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
      strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
      fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_FROM],
               _(KeyInfoPrompts[KIP_VALID_FROM]), shortbuf);
    }

  if (key->subkeys && (key->subkeys->expires > 0))
    {
      tt = key->subkeys->expires;

      tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
      strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
      strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
      fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_TO],
               _(KeyInfoPrompts[KIP_VALID_TO]), shortbuf);
    }

  if (key->subkeys)
    s = gpgme_pubkey_algo_name (key->subkeys->pubkey_algo);
  else
    s = "?";

  s2 = is_pgp ? "PGP" : "X.509";

  if (key->subkeys)
    aval = key->subkeys->length;

  fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_TYPE],
           _(KeyInfoPrompts[KIP_KEY_TYPE]));
  /* L10N: This is printed after "Key Type: " and looks like this:
   *       PGP, 2048 bit RSA */
  fprintf (fp, _("%s, %lu bit %s\n"), s2, aval, s);

  fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_USAGE],
           _(KeyInfoPrompts[KIP_KEY_USAGE]));
  delim = "";

  if (key_check_cap (key, KEY_CAP_CAN_ENCRYPT))
    {
      /* L10N: value in Key Usage: field */
      fprintf (fp, "%s%s", delim, _("encryption"));
      delim = _(", ");
    }
  if (key_check_cap (key, KEY_CAP_CAN_SIGN))
    {
      /* L10N: value in Key Usage: field */
      fprintf (fp, "%s%s", delim, _("signing"));
      delim = _(", ");
    }
  if (key_check_cap (key, KEY_CAP_CAN_CERTIFY))
    {
      /* L10N: value in Key Usage: field */
      fprintf (fp, "%s%s", delim, _("certification"));
      delim = _(", ");
    }
  putc ('\n', fp);

  if (key->subkeys)
    {
      s = key->subkeys->fpr;
      fprintf (fp, "%*s", KeyInfoPadding[KIP_FINGERPRINT],
               _(KeyInfoPrompts[KIP_FINGERPRINT]));
      if (is_pgp && strlen (s) == 40)
        {
          for (i=0; *s && s[1] && s[2] && s[3] && s[4]; s += 4, i++)
            {
              putc (*s, fp);
              putc (s[1], fp);
              putc (s[2], fp);
              putc (s[3], fp);
              putc (is_pgp? ' ':':', fp);
              if (is_pgp && i == 4)
                putc (' ', fp);
            }
        }
      else
        {
          for (i=0; *s && s[1] && s[2]; s += 2, i++)
            {
              putc (*s, fp);
              putc (s[1], fp);
              putc (is_pgp? ' ':':', fp);
              if (is_pgp && i == 7)
                putc (' ', fp);
            }
        }
      fprintf (fp, "%s\n", s);
    }

  if (key->issuer_serial)
    {
      s = key->issuer_serial;
      if (s)
        fprintf (fp, "%*s0x%s\n", KeyInfoPadding[KIP_SERIAL_NO],
                 _(KeyInfoPrompts[KIP_SERIAL_NO]), s);
    }

  if (key->issuer_name)
    {
      s = key->issuer_name;
      if (s)
	{
          fprintf (fp, "%*s", KeyInfoPadding[KIP_ISSUED_BY],
                 _(KeyInfoPrompts[KIP_ISSUED_BY]));
	  parse_and_print_user_id (fp, s);
	  putc ('\n', fp);
	}
    }

  /* For PGP we list all subkeys. */
  if (is_pgp)
    {
      gpgme_subkey_t subkey = NULL;

      for (idx = 1, subkey = key->subkeys; subkey;
           idx++, subkey = subkey->next)
        {
	  s = subkey->keyid;

          putc ('\n', fp);
          if ( strlen (s) == 16)
            s += 8; /* display only the short keyID */
          fprintf (fp, "%*s0x%s", KeyInfoPadding[KIP_SUBKEY],
                 _(KeyInfoPrompts[KIP_SUBKEY]), s);
	  if (subkey->revoked)
            {
              putc (' ', fp);
              /* L10N: describes a subkey */
              fputs (_("[Revoked]"), fp);
            }
	  if (subkey->invalid)
            {
              putc (' ', fp);
              /* L10N: describes a subkey */
              fputs (_("[Invalid]"), fp);
            }
	  if (subkey->expired)
            {
              putc (' ', fp);
              /* L10N: describes a subkey */
              fputs (_("[Expired]"), fp);
            }
	  if (subkey->disabled)
            {
              putc (' ', fp);
              /* L10N: describes a subkey */
              fputs (_("[Disabled]"), fp);
            }
          putc ('\n', fp);

	  if (subkey->timestamp > 0)
	    {
	      tt = subkey->timestamp;

              tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
              strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
              strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
              fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_FROM],
                       _(KeyInfoPrompts[KIP_VALID_FROM]), shortbuf);
            }

	  if (subkey->expires > 0)
	    {
	      tt = subkey->expires;

              tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
              strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
              strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
              fprintf (fp, "%*s%s\n", KeyInfoPadding[KIP_VALID_TO],
                       _(KeyInfoPrompts[KIP_VALID_TO]), shortbuf);
            }

	  if (subkey)
	    s = gpgme_pubkey_algo_name (subkey->pubkey_algo);
	  else
            s = "?";

	  if (subkey)
	    aval = subkey->length;
	  else
	    aval = 0;

          fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_TYPE],
                   _(KeyInfoPrompts[KIP_KEY_TYPE]));
          fprintf (fp, _("%s, %lu bit %s\n"), "PGP", aval, s);

          fprintf (fp, "%*s", KeyInfoPadding[KIP_KEY_USAGE],
                   _(KeyInfoPrompts[KIP_KEY_USAGE]));
          delim = "";

	  if (subkey->can_encrypt)
            {
              fprintf (fp, "%s%s", delim, _("encryption"));
              delim = _(", ");
            }
          if (subkey->can_sign)
            {
              fprintf (fp, "%s%s", delim, _("signing"));
              delim = _(", ");
            }
          if (subkey->can_certify)
            {
              fprintf (fp, "%s%s", delim, _("certification"));
              delim = _(", ");
            }
          putc ('\n', fp);
        }
    }
}