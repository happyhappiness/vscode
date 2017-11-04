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

  is_pgp = key->protocol == GPGME_PROTOCOL_OpenPGP;

  for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
    {
      if (uid->revoked)
        continue;

      s = uid->uid;
      /* L10N:
         Fill dots to make the DOTFILL entries the same length.
         In English, msgid "Fingerprint: " is the longest entry for this menu.
         Your language may vary. */
      fputs (idx ? _(" aka ......: ") :_("Name ......: "), fp);
      if (uid->invalid)
        {
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
      /* L10N: DOTFILL */
      fprintf (fp, _("Valid From : %s\n"), shortbuf);
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
      /* L10N: DOTFILL */
      fprintf (fp, _("Valid To ..: %s\n"), shortbuf);
    }

  if (key->subkeys)
    s = gpgme_pubkey_algo_name (key->subkeys->pubkey_algo);
  else
    s = "?";

  s2 = is_pgp ? "PGP" : "X.509";

  if (key->subkeys)
    aval = key->subkeys->length;

  /* L10N: DOTFILL */
  fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), s2, aval, s);

  /* L10N: DOTFILL */
  fprintf (fp, _("Key Usage .: "));
  delim = "";

  if (key_check_cap (key, KEY_CAP_CAN_ENCRYPT))
    {
      fprintf (fp, "%s%s", delim, _("encryption"));
      delim = _(", ");
    }
  if (key_check_cap (key, KEY_CAP_CAN_SIGN))
    {
      fprintf (fp, "%s%s", delim, _("signing"));
      delim = _(", ");
    }
  if (key_check_cap (key, KEY_CAP_CAN_CERTIFY))
    {
      fprintf (fp, "%s%s", delim, _("certification"));
      delim = _(", ");
    }
  putc ('\n', fp);

  if (key->subkeys)
    {
      s = key->subkeys->fpr;
      /* L10N: DOTFILL */
      fputs (_("Fingerprint: "), fp);
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
        /* L10N: DOTFILL */
	fprintf (fp, _("Serial-No .: 0x%s\n"), s);
    }

  if (key->issuer_name)
    {
      s = key->issuer_name;
      if (s)
	{
          /* L10N: DOTFILL */
	  fprintf (fp, _("Issued By .: "));
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
          /* L10N: DOTFILL */
          fprintf (fp, _("Subkey ....: 0x%s"), s);
	  if (subkey->revoked)
            {
              putc (' ', fp);
              fputs (_("[Revoked]"), fp);
            }
	  if (subkey->invalid)
            {
              putc (' ', fp);
              fputs (_("[Invalid]"), fp);
            }
	  if (subkey->expired)
            {
              putc (' ', fp);
              fputs (_("[Expired]"), fp);
            }
	  if (subkey->disabled)
            {
              putc (' ', fp);
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
              /* L10N: DOTFILL */
              fprintf (fp, _("Valid From : %s\n"), shortbuf);
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
              /* L10N: DOTFILL */
              fprintf (fp, _("Valid To ..: %s\n"), shortbuf);
            }

	  if (subkey)
	    s = gpgme_pubkey_algo_name (subkey->pubkey_algo);
	  else
            s = "?";

	  if (subkey)
	    aval = subkey->length;
	  else
	    aval = 0;

          /* L10N: DOTFILL */
          fprintf (fp, _("Key Type ..: %s, %lu bit %s\n"), "PGP", aval, s);

          /* L10N: DOTFILL */
          fprintf (fp, _("Key Usage .: "));
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