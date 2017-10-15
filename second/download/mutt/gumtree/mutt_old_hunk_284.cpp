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
