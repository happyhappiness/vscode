static int interactive_check_cert (X509 *cert, int idx, int len)
{
  static const char * const part[] =
    {"/CN=", "/Email=", "/O=", "/OU=", "/L=", "/ST=", "/C="};
  char helpstr[LONG_STRING];
  char buf[STRING];
  char title[STRING];
  MUTTMENU *menu = mutt_new_menu (MENU_GENERIC);
  int done, row, i;
  FILE *fp;
  char *name = NULL, *c;

  menu->max = 19;
  menu->dialog = (char **) safe_calloc (1, menu->max * sizeof (char *));
  for (i = 0; i < menu->max; i++)
    menu->dialog[i] = (char *) safe_calloc (1, SHORT_STRING * sizeof (char));

  row = 0;
  strfcpy (menu->dialog[row], _("This certificate belongs to:"), SHORT_STRING);
  row++;
  name = X509_NAME_oneline (X509_get_subject_name (cert),
			    buf, sizeof (buf));

  for (i = 0; i < 5; i++)
  {
    c = x509_get_part (name, part[i]);
    snprintf (menu->dialog[row++], SHORT_STRING, "   %s", c);
  }

  row++;
  strfcpy (menu->dialog[row], _("This certificate was issued by:"), SHORT_STRING);
  row++;
  name = X509_NAME_oneline (X509_get_issuer_name (cert),
			    buf, sizeof (buf));
  for (i = 0; i < 5; i++)
  {
    c = x509_get_part (name, part[i]);
    snprintf (menu->dialog[row++], SHORT_STRING, "   %s", c);
  }

  row++;
  snprintf (menu->dialog[row++], SHORT_STRING, _("This certificate is valid"));
  snprintf (menu->dialog[row++], SHORT_STRING, _("   from %s"),
      asn1time_to_string (X509_get_notBefore (cert)));
  snprintf (menu->dialog[row++], SHORT_STRING, _("     to %s"),
      asn1time_to_string (X509_get_notAfter (cert)));

  row++;
  buf[0] = '\0';
  x509_fingerprint (buf, sizeof (buf), cert);
  snprintf (menu->dialog[row++], SHORT_STRING, _("Fingerprint: %s"), buf);

  snprintf (title, sizeof (title),
	    _("SSL Certificate check (certificate %d of %d in chain)"),
	    len - idx, len);
  menu->title = title;
  if (SslCertFile
      && (option (OPTSSLVERIFYDATES) == MUTT_NO
	  || (X509_cmp_current_time (X509_get_notAfter (cert)) >= 0
	      && X509_cmp_current_time (X509_get_notBefore (cert)) < 0)))
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
	ssl_cache_trusted_cert (cert);
        break;
    }
  }
  unset_option(OPTIGNOREMACROEVENTS);
  mutt_menuDestroy (&menu);
  dprint (2, (debugfile, "ssl interactive_check_cert: done=%d\n", done));
  return (done == 2);
}