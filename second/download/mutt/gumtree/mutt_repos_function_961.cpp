static int tls_check_one_certificate (const gnutls_datum_t *certdata,
                                      gnutls_certificate_status_t certstat,
                                      const char* hostname, int idx, int len)
{
  int certerr, savedcert;
  gnutls_x509_crt_t cert;
  char buf[SHORT_STRING];
  char fpbuf[SHORT_STRING];
  size_t buflen;
  char dn_common_name[SHORT_STRING];
  char dn_email[SHORT_STRING];
  char dn_organization[SHORT_STRING];
  char dn_organizational_unit[SHORT_STRING];
  char dn_locality[SHORT_STRING];
  char dn_province[SHORT_STRING];
  char dn_country[SHORT_STRING];
  time_t t;
  char datestr[30];
  MUTTMENU *menu;
  char helpstr[LONG_STRING];
  char title[STRING];
  FILE *fp;
  gnutls_datum_t pemdata;
  int i, row, done, ret;

  if (!tls_check_preauth (certdata, certstat, hostname, idx, &certerr,
      &savedcert))
    return 1;

  /* skip signers if insecure algorithm was used */
  if (idx && (certerr & CERTERR_INSECUREALG))
  {
    if (idx == 1)
    {
      mutt_error (_("Warning: Server certificate was signed using an insecure algorithm"));
      mutt_sleep (2);
    }
    return 0;
  }

  /* interactive check from user */
  if (gnutls_x509_crt_init (&cert) < 0)
  {
    mutt_error (_("Error initialising gnutls certificate data"));
    mutt_sleep (2);
    return 0;
  }

  if (gnutls_x509_crt_import (cert, certdata, GNUTLS_X509_FMT_DER) < 0)
  {
    mutt_error (_("Error processing certificate data"));
    mutt_sleep (2);
    gnutls_x509_crt_deinit (cert);
    return 0;
  }

  menu = mutt_new_menu (MENU_GENERIC);
  menu->max = 25;
  menu->dialog = (char **) safe_calloc (1, menu->max * sizeof (char *));
  for (i = 0; i < menu->max; i++)
    menu->dialog[i] = (char *) safe_calloc (1, SHORT_STRING * sizeof (char));

  row = 0;
  strfcpy (menu->dialog[row], _("This certificate belongs to:"), SHORT_STRING);
  row++;

  buflen = sizeof (dn_common_name);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_X520_COMMON_NAME, 0, 0,
                                     dn_common_name, &buflen) != 0)
    dn_common_name[0] = '\0';
  buflen = sizeof (dn_email);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_PKCS9_EMAIL, 0, 0,
                                     dn_email, &buflen) != 0)
    dn_email[0] = '\0';
  buflen = sizeof (dn_organization);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_X520_ORGANIZATION_NAME, 0, 0,
                                     dn_organization, &buflen) != 0)
    dn_organization[0] = '\0';
  buflen = sizeof (dn_organizational_unit);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_X520_ORGANIZATIONAL_UNIT_NAME, 0, 0,
                                     dn_organizational_unit, &buflen) != 0)
    dn_organizational_unit[0] = '\0';
  buflen = sizeof (dn_locality);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_X520_LOCALITY_NAME, 0, 0,
                                     dn_locality, &buflen) != 0)
    dn_locality[0] = '\0';
  buflen = sizeof (dn_province);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_X520_STATE_OR_PROVINCE_NAME, 0, 0,
                                     dn_province, &buflen) != 0)
    dn_province[0] = '\0';
  buflen = sizeof (dn_country);
  if (gnutls_x509_crt_get_dn_by_oid (cert, GNUTLS_OID_X520_COUNTRY_NAME, 0, 0,
                                     dn_country, &buflen) != 0)
    dn_country[0] = '\0';

  snprintf (menu->dialog[row++], SHORT_STRING, "   %s  %s", dn_common_name, dn_email);
  snprintf (menu->dialog[row++], SHORT_STRING, "   %s", dn_organization);
  snprintf (menu->dialog[row++], SHORT_STRING, "   %s", dn_organizational_unit);
  snprintf (menu->dialog[row++], SHORT_STRING, "   %s  %s  %s",
            dn_locality, dn_province, dn_country);
  row++;

  strfcpy (menu->dialog[row], _("This certificate was issued by:"), SHORT_STRING);
  row++;

  buflen = sizeof (dn_common_name);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_X520_COMMON_NAME, 0, 0,
                                            dn_common_name, &buflen) != 0)
    dn_common_name[0] = '\0';
  buflen = sizeof (dn_email);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_PKCS9_EMAIL, 0, 0,
                                            dn_email, &buflen) != 0)
    dn_email[0] = '\0';
  buflen = sizeof (dn_organization);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_X520_ORGANIZATION_NAME, 0, 0,
                                            dn_organization, &buflen) != 0)
    dn_organization[0] = '\0';
  buflen = sizeof (dn_organizational_unit);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_X520_ORGANIZATIONAL_UNIT_NAME, 0, 0,
                                            dn_organizational_unit, &buflen) != 0)
    dn_organizational_unit[0] = '\0';
  buflen = sizeof (dn_locality);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_X520_LOCALITY_NAME, 0, 0,
                                            dn_locality, &buflen) != 0)
    dn_locality[0] = '\0';
  buflen = sizeof (dn_province);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_X520_STATE_OR_PROVINCE_NAME, 0, 0,
                                            dn_province, &buflen) != 0)
    dn_province[0] = '\0';
  buflen = sizeof (dn_country);
  if (gnutls_x509_crt_get_issuer_dn_by_oid (cert, GNUTLS_OID_X520_COUNTRY_NAME, 0, 0,
                                            dn_country, &buflen) != 0)
    dn_country[0] = '\0';

  snprintf (menu->dialog[row++], SHORT_STRING, "   %s  %s", dn_common_name, dn_email);
  snprintf (menu->dialog[row++], SHORT_STRING, "   %s", dn_organization);
  snprintf (menu->dialog[row++], SHORT_STRING, "   %s", dn_organizational_unit);
  snprintf (menu->dialog[row++], SHORT_STRING, "   %s  %s  %s",
            dn_locality, dn_province, dn_country);
  row++;

  snprintf (menu->dialog[row++], SHORT_STRING, _("This certificate is valid"));

  t = gnutls_x509_crt_get_activation_time (cert);
  snprintf (menu->dialog[row++], SHORT_STRING, _("   from %s"),
	    tls_make_date (t, datestr, 30));

  t = gnutls_x509_crt_get_expiration_time (cert);
  snprintf (menu->dialog[row++], SHORT_STRING, _("     to %s"),
	    tls_make_date (t, datestr, 30));

  fpbuf[0] = '\0';
  tls_fingerprint (GNUTLS_DIG_SHA, fpbuf, sizeof (fpbuf), certdata);
  snprintf (menu->dialog[row++], SHORT_STRING, _("SHA1 Fingerprint: %s"), fpbuf);
  fpbuf[0] = '\0';
  tls_fingerprint (GNUTLS_DIG_MD5, fpbuf, sizeof (fpbuf), certdata);
  snprintf (menu->dialog[row++], SHORT_STRING, _("MD5 Fingerprint: %s"), fpbuf);

  if (certerr & CERTERR_NOTYETVALID)
  {
    row++;
    strfcpy (menu->dialog[row], _("WARNING: Server certificate is not yet valid"), SHORT_STRING);
  }
  if (certerr & CERTERR_EXPIRED)
  {
    row++;
    strfcpy (menu->dialog[row], _("WARNING: Server certificate has expired"), SHORT_STRING);
  }
  if (certerr & CERTERR_REVOKED)
  {
    row++;
    strfcpy (menu->dialog[row], _("WARNING: Server certificate has been revoked"), SHORT_STRING);
  }
  if (certerr & CERTERR_HOSTNAME)
  {
    row++;
    strfcpy (menu->dialog[row], _("WARNING: Server hostname does not match certificate"), SHORT_STRING);
  }
  if (certerr & CERTERR_SIGNERNOTCA)
  {
    row++;
    strfcpy (menu->dialog[row], _("WARNING: Signer of server certificate is not a CA"), SHORT_STRING);
  }

  snprintf (title, sizeof (title),
            _("SSL Certificate check (certificate %d of %d in chain)"),
            len - idx, len);
  menu->title = title;
  /* certificates with bad dates, or that are revoked, must be
   accepted manually each and every time */
  if (SslCertFile && !savedcert
        && !(certerr & (CERTERR_EXPIRED | CERTERR_NOTYETVALID
                        | CERTERR_REVOKED)))
  {
    menu->prompt = _("(r)eject, accept (o)nce, (a)ccept always");
    menu->keys = _("roa");
  }
  else
  {
    menu->prompt = _("(r)eject, accept (o)nce");
    menu->keys = _("ro");
  }

  helpstr[0] = '\0';
  mutt_make_help (buf, sizeof (buf), _("Exit  "), MENU_GENERIC, OP_EXIT);
  safe_strcat (helpstr, sizeof (helpstr), buf);
  mutt_make_help (buf, sizeof (buf), _("Help"), MENU_GENERIC, OP_HELP);
  safe_strcat (helpstr, sizeof (helpstr), buf);
  menu->help = helpstr;

  done = 0;
  set_option (OPTIGNOREMACROEVENTS);
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
        done = 0;
        if ((fp = fopen (SslCertFile, "a")))
	{
	  /* save hostname if necessary */
	  if (certerr & CERTERR_HOSTNAME)
	  {
	    fprintf(fp, "#H %s %s\n", hostname, fpbuf);
	    done = 1;
	  }
	  if (certerr & CERTERR_NOTTRUSTED)
	  {
            done = 0;
	    ret = gnutls_pem_base64_encode_alloc ("CERTIFICATE", certdata,
                                                  &pemdata);
	    if (ret == 0)
	    {
	      if (fwrite (pemdata.data, pemdata.size, 1, fp) == 1)
	      {
		done = 1;
	      }
              gnutls_free (pemdata.data);
	    }
	  }
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
        break;
    }
  }
  unset_option (OPTIGNOREMACROEVENTS);
  mutt_menuDestroy (&menu);
  gnutls_x509_crt_deinit (cert);

  return (done == 2);
}