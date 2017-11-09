static int interactive_check_cert (X509 *cert, int idx, int len, SSL *ssl, int allow_always)
{
  static const int part[] =
    { NID_commonName,             /* CN */
      NID_pkcs9_emailAddress,     /* Email */
      NID_organizationName,       /* O */
      NID_organizationalUnitName, /* OU */
      NID_localityName,           /* L */
      NID_stateOrProvinceName,    /* ST */
      NID_countryName             /* C */ };
  X509_NAME *x509_subject;
  X509_NAME *x509_issuer;
  char helpstr[LONG_STRING];
  char buf[STRING];
  char title[STRING];
  MUTTMENU *menu = mutt_new_menu (MENU_GENERIC);
  int done, row, i;
  unsigned u;
  FILE *fp;
  int allow_skip = 0;

  mutt_push_current_menu (menu);

  menu->max = mutt_array_size (part) * 2 + 10;
  menu->dialog = (char **) safe_calloc (1, menu->max * sizeof (char *));
  for (i = 0; i < menu->max; i++)
    menu->dialog[i] = (char *) safe_calloc (1, SHORT_STRING * sizeof (char));

  row = 0;
  strfcpy (menu->dialog[row], _("This certificate belongs to:"), SHORT_STRING);
  row++;
  x509_subject = X509_get_subject_name (cert);
  for (u = 0; u < mutt_array_size (part); u++)
    snprintf (menu->dialog[row++], SHORT_STRING, "   %s",
              x509_get_part (x509_subject, part[u]));

  row++;
  strfcpy (menu->dialog[row], _("This certificate was issued by:"), SHORT_STRING);
  row++;
  x509_issuer = X509_get_issuer_name (cert);
  for (u = 0; u < mutt_array_size (part); u++)
    snprintf (menu->dialog[row++], SHORT_STRING, "   %s",
              x509_get_part (x509_issuer, part[u]));

  row++;
  snprintf (menu->dialog[row++], SHORT_STRING, "%s", _("This certificate is valid"));
  snprintf (menu->dialog[row++], SHORT_STRING, _("   from %s"),
      asn1time_to_string (X509_get_notBefore (cert)));
  snprintf (menu->dialog[row++], SHORT_STRING, _("     to %s"),
      asn1time_to_string (X509_get_notAfter (cert)));

  row++;
  buf[0] = '\0';
  x509_fingerprint (buf, sizeof (buf), cert, EVP_sha1);
  snprintf (menu->dialog[row++], SHORT_STRING, _("SHA1 Fingerprint: %s"), buf);
  buf[0] = '\0';
  x509_fingerprint (buf, sizeof (buf), cert, EVP_md5);
  snprintf (menu->dialog[row++], SHORT_STRING, _("MD5 Fingerprint: %s"), buf);

  snprintf (title, sizeof (title),
	    _("SSL Certificate check (certificate %d of %d in chain)"),
	    len - idx, len);
  menu->title = title;

  /* The leaf/host certificate can't be skipped. */
#ifdef HAVE_SSL_PARTIAL_CHAIN
  if ((idx != 0) &&
      (option (OPTSSLVERIFYPARTIAL)))
    allow_skip = 1;
#endif

  /* Inside ssl_verify_callback(), this function is guarded by a call to
   * check_certificate_by_digest().  This means if check_certificate_expiration() is
   * true, then check_certificate_file() must be false.  Therefore we don't need
   * to also scan the certificate file here.
   */
  allow_always = allow_always &&
                 SslCertFile &&
                 check_certificate_expiration (cert, 1);

  /* L10N:
   * These four letters correspond to the choices in the next four strings:
   * (r)eject, accept (o)nce, (a)ccept always, (s)kip.
   * These prompts are the interactive certificate confirmation prompts for
   * an OpenSSL connection.
   */
  menu->keys = _("roas");
  if (allow_always)
  {
    if (allow_skip)
      menu->prompt = _("(r)eject, accept (o)nce, (a)ccept always, (s)kip");
    else
      menu->prompt = _("(r)eject, accept (o)nce, (a)ccept always");
  }
  else
  {
    if (allow_skip)
      menu->prompt = _("(r)eject, accept (o)nce, (s)kip");
    else
      menu->prompt = _("(r)eject, accept (o)nce");
  }

  helpstr[0] = '\0';
  mutt_make_help (buf, sizeof (buf), _("Exit  "), MENU_GENERIC, OP_EXIT);
  safe_strcat (helpstr, sizeof (helpstr), buf);
  mutt_make_help (buf, sizeof (buf), _("Help"), MENU_GENERIC, OP_HELP);
  safe_strcat (helpstr, sizeof (helpstr), buf);
  menu->help = helpstr;

  done = 0;
  set_option(OPTIGNOREMACROEVENTS);
  while (!done)
  {
    switch (mutt_menuLoop (menu))
    {
      case -1:			/* abort */
      case OP_MAX + 1:		/* reject */
      case OP_EXIT:
        done = 1;
        break;
      case OP_MAX + 3:		/* accept always */
        if (!allow_always)
          break;
        done = 0;
        if ((fp = fopen (SslCertFile, "a")))
	{
	  if (PEM_write_X509 (fp, cert))
	    done = 1;
	  safe_fclose (&fp);
	}
	if (!done)
        {
	  mutt_error (_("Warning: Couldn't save certificate"));
	  mutt_sleep (2);
	}
	else
        {
	  mutt_message (_("Certificate saved"));
	  mutt_sleep (0);
	}
        /* fall through */
      case OP_MAX + 2:		/* accept once */
        done = 2;
        SSL_set_ex_data (ssl, SkipModeExDataIndex, NULL);
	ssl_cache_trusted_cert (cert);
        break;
      case OP_MAX + 4:          /* skip */
        if (!allow_skip)
          break;
        done = 2;
        SSL_set_ex_data (ssl, SkipModeExDataIndex, &SkipModeExDataIndex);
        break;
    }
  }
  unset_option(OPTIGNOREMACROEVENTS);
  mutt_pop_current_menu (menu);
  mutt_menuDestroy (&menu);
  dprint (2, (debugfile, "ssl interactive_check_cert: done=%d\n", done));
  return (done == 2);
}