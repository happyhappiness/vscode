static int ssl_check_certificate (sslsockdata * data)
{
  char *part[] =
  {"/CN=", "/Email=", "/O=", "/OU=", "/L=", "/ST=", "/C="};
  char helpstr[SHORT_STRING];
  char buf[SHORT_STRING];
  MUTTMENU *menu;
  int done, row, i;
  FILE *fp;
  char *name = NULL, *c;

  if (check_certificate_by_signer (data->cert))
  {
    dprint (1, (debugfile, "ssl_check_certificate: signer check passed\n"));
    return 1;
  }

  /* automatic check from user's database */
  if (SslCertFile && check_certificate_by_digest (data->cert))
  {
    dprint (1, (debugfile, "ssl_check_certificate: digest check passed\n"));
    return 1;
  }

  /* interactive check from user */
  menu = mutt_new_menu ();
  menu->max = 19;
  menu->dialog = (char **) safe_calloc (1, menu->max * sizeof (char *));
  for (i = 0; i < menu->max; i++)
    menu->dialog[i] = (char *) safe_calloc (1, SHORT_STRING * sizeof (char));

  row = 0;
  strfcpy (menu->dialog[row], _("This certificate belongs to:"), SHORT_STRING);
  row++;
  name = X509_NAME_oneline (X509_get_subject_name (data->cert),
			    buf, sizeof (buf));
  for (i = 0; i < 5; i++)
  {
    c = x509_get_part (name, part[i]);
    snprintf (menu->dialog[row++], SHORT_STRING, "   %s", c);
  }

  row++;
  strfcpy (menu->dialog[row], _("This certificate was issued by:"), SHORT_STRING);
  row++;
  name = X509_NAME_oneline (X509_get_issuer_name (data->cert),
			    buf, sizeof (buf));
  for (i = 0; i < 5; i++)
  {
    c = x509_get_part (name, part[i]);
    snprintf (menu->dialog[row++], SHORT_STRING, "   %s", c);
  }

  row++;
  snprintf (menu->dialog[row++], SHORT_STRING, _("This certificate is valid"));
  snprintf (menu->dialog[row++], SHORT_STRING, _("   from %s"), 
      asn1time_to_string (X509_get_notBefore (data->cert)));
  snprintf (menu->dialog[row++], SHORT_STRING, _("     to %s"), 
      asn1time_to_string (X509_get_notAfter (data->cert)));

  row++;
  buf[0] = '\0';
  x509_fingerprint (buf, sizeof (buf), data->cert);
  snprintf (menu->dialog[row++], SHORT_STRING, _("Fingerprint: %s"), buf);

  menu->title = _("SSL Certificate check");
  if (SslCertFile)
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
  strncat (helpstr, buf, sizeof (helpstr));
  mutt_make_help (buf, sizeof (buf), _("Help"), MENU_GENERIC, OP_HELP);
  strncat (helpstr, buf, sizeof (helpstr));
  menu->help = helpstr;

  done = 0;
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
	  if (PEM_write_X509 (fp, data->cert))
	    done = 1;
	  fclose (fp);
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
  mutt_menuDestroy (&menu);
  return (done == 2);
}