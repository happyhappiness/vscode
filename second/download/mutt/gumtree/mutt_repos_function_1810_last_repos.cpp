void mutt_init (int skip_sys_rc, LIST *commands)
{
  struct passwd *pw;
  struct utsname utsname;
  char *p, buffer[STRING];
  char *domain = NULL;
  int i, need_pause = 0;
  BUFFER err;

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc(err.dsize);
  err.dptr = err.data;

  Groups = hash_create (1031, 0);
  /* reverse alias keys need to be strdup'ed because of idna conversions */
  ReverseAlias = hash_create (1031, MUTT_HASH_STRCASECMP | MUTT_HASH_STRDUP_KEYS |
                              MUTT_HASH_ALLOW_DUPS);
  
  mutt_menu_init ();
  mutt_srandom ();

  /* 
   * XXX - use something even more difficult to predict?
   */
  snprintf (AttachmentMarker, sizeof (AttachmentMarker),
	    "\033]9;%ld\a", (long) time (NULL));
  
  /* on one of the systems I use, getcwd() does not return the same prefix
     as is listed in the passwd file */
  if ((p = getenv ("HOME")))
    Homedir = safe_strdup (p);

  /* Get some information about the user */
  if ((pw = getpwuid (getuid ())))
  {
    char rnbuf[STRING];

    Username = safe_strdup (pw->pw_name);
    if (!Homedir)
      Homedir = safe_strdup (pw->pw_dir);

    Realname = safe_strdup (mutt_gecos_name (rnbuf, sizeof (rnbuf), pw));
    Shell = safe_strdup (pw->pw_shell);
    endpwent ();
  }
  else 
  {
    if (!Homedir)
    {
      mutt_endwin (NULL);
      fputs (_("unable to determine home directory"), stderr);
      exit (1);
    }
    if ((p = getenv ("USER")))
      Username = safe_strdup (p);
    else
    {
      mutt_endwin (NULL);
      fputs (_("unable to determine username"), stderr);
      exit (1);
    }
    Shell = safe_strdup ((p = getenv ("SHELL")) ? p : "/bin/sh");
  }

#ifdef DEBUG
  /* Start up debugging mode if requested */
  if (debuglevel > 0)
    start_debug ();
#endif

  /* And about the host... */

#ifdef DOMAIN
  domain = safe_strdup (DOMAIN);
#endif /* DOMAIN */

  /*
   * The call to uname() shouldn't fail, but if it does, the system is horribly
   * broken, and the system's networking configuration is in an unreliable
   * state.  We should bail.
   */
  if ((uname (&utsname)) == -1)
  {
    mutt_endwin (NULL);
    perror (_("unable to determine nodename via uname()"));
    exit (1);
  }

  /* some systems report the FQDN instead of just the hostname */
  if ((p = strchr (utsname.nodename, '.')))
    Hostname = mutt_substrdup (utsname.nodename, p);
  else
    Hostname = safe_strdup (utsname.nodename);

  /* now get FQDN.  Use configured domain first, DNS next, then uname */
  if (domain)
  {
    /* we have a compile-time domain name, use that for Fqdn */
    Fqdn = safe_malloc (mutt_strlen (domain) + mutt_strlen (Hostname) + 2);
    sprintf (Fqdn, "%s.%s", NONULL(Hostname), domain);	/* __SPRINTF_CHECKED__ */
  }
  else if (!(getdnsdomainname (buffer, sizeof buffer)))
  {
    Fqdn = safe_malloc (mutt_strlen (buffer) + mutt_strlen (Hostname) + 2);
    sprintf (Fqdn, "%s.%s", NONULL(Hostname), buffer);	/* __SPRINTF_CHECKED__ */
  }
  else
    /*
     * DNS failed, use the nodename.  Whether or not the nodename had a '.' in
     * it, we can use the nodename as the FQDN.  On hosts where DNS is not
     * being used, e.g. small network that relies on hosts files, a short host
     * name is all that is required for SMTP to work correctly.  It could be
     * wrong, but we've done the best we can, at this point the onus is on the
     * user to provide the correct hostname if the nodename won't work in their
     * network.
     */
    Fqdn = safe_strdup(utsname.nodename);


  if ((p = getenv ("MAIL")))
    Spoolfile = safe_strdup (p);
  else if ((p = getenv ("MAILDIR")))
    Spoolfile = safe_strdup (p);
  else
  {
#ifdef HOMESPOOL
    mutt_concat_path (buffer, NONULL (Homedir), MAILPATH, sizeof (buffer));
#else
    mutt_concat_path (buffer, MAILPATH, NONULL(Username), sizeof (buffer));
#endif
    Spoolfile = safe_strdup (buffer);
  }

  if ((p = getenv ("MAILCAPS")))
    MailcapPath = safe_strdup (p);
  else
  {
    /* Default search path from RFC1524 */
    MailcapPath = safe_strdup ("~/.mailcap:" PKGDATADIR "/mailcap:" SYSCONFDIR "/mailcap:/etc/mailcap:/usr/etc/mailcap:/usr/local/etc/mailcap");
  }

  Tempdir = safe_strdup ((p = getenv ("TMPDIR")) ? p : "/tmp");

  p = getenv ("VISUAL");
  if (!p)
  {
    p = getenv ("EDITOR");
    if (!p)
      p = "vi";
  }
  Editor = safe_strdup (p);
  Visual = safe_strdup (p);

  if ((p = getenv ("REPLYTO")) != NULL)
  {
    BUFFER buf, token;

    snprintf (buffer, sizeof (buffer), "Reply-To: %s", p);

    mutt_buffer_init (&buf);
    buf.data = buf.dptr = buffer;
    buf.dsize = mutt_strlen (buffer);

    mutt_buffer_init (&token);
    parse_my_hdr (&token, &buf, 0, &err);
    FREE (&token.data);
  }

  if ((p = getenv ("EMAIL")) != NULL)
    From = rfc822_parse_adrlist (NULL, p);
  
  mutt_set_langinfo_charset ();
  mutt_set_charset (Charset);
  
  Matches = safe_calloc (Matches_listsize, sizeof (char *));
  
  /* Set standard defaults */
  for (i = 0; MuttVars[i].option; i++)
  {
    mutt_set_default (&MuttVars[i]);
    mutt_restore_default (&MuttVars[i]);
  }

  CurrentMenu = MENU_MAIN;


#ifndef LOCALES_HACK
  /* Do we have a locale definition? */
  if (((p = getenv ("LC_ALL")) != NULL && p[0]) ||
      ((p = getenv ("LANG")) != NULL && p[0]) ||
      ((p = getenv ("LC_CTYPE")) != NULL && p[0]))
    set_option (OPTLOCALES);
#endif

#ifdef HAVE_GETSID
  /* Unset suspend by default if we're the session leader */
  if (getsid(0) == getpid())
    unset_option (OPTSUSPEND);
#endif

  mutt_init_history ();

  /* RFC2368, "4. Unsafe headers"
   * The creator of a mailto URL cannot expect the resolver of a URL to
   * understand more than the "subject" and "body" headers. Clients that
   * resolve mailto URLs into mail messages should be able to correctly
   * create RFC 822-compliant mail messages using the "subject" and "body"
   * headers.
   */
  add_to_list(&MailtoAllow, "body");
  add_to_list(&MailtoAllow, "subject");
  
  
  
  /*
   * 
   *			   BIG FAT WARNING
   * 
   * When changing the code which looks for a configuration file,
   * please also change the corresponding code in muttbug.sh.in.
   * 
   * 
   */

  if (!Muttrc)
  {
    char *xdg_cfg_home = getenv ("XDG_CONFIG_HOME");

    if (!xdg_cfg_home && Homedir)
    {
      snprintf (buffer, sizeof (buffer), "%s/.config", Homedir);
      xdg_cfg_home = buffer;
    }

    Muttrc = mutt_find_cfg (Homedir, xdg_cfg_home);
  }
  else
  {
    strfcpy (buffer, Muttrc, sizeof (buffer));
    FREE (&Muttrc);
    mutt_expand_path (buffer, sizeof (buffer));
    Muttrc = safe_strdup (buffer);
    if (access (Muttrc, F_OK))
    {
      snprintf (buffer, sizeof (buffer), "%s: %s", Muttrc, strerror (errno));
      mutt_endwin (buffer);
      exit (1);
    }
  }

  if (Muttrc)
  {
    FREE (&AliasFile);
    AliasFile = safe_strdup (Muttrc);
  }

  /* Process the global rc file if it exists and the user hasn't explicity
     requested not to via "-n".  */
  if (!skip_sys_rc)
  {
    snprintf (buffer, sizeof(buffer), "%s/Muttrc-%s", SYSCONFDIR, MUTT_VERSION);
    if (access (buffer, F_OK) == -1)
      snprintf (buffer, sizeof(buffer), "%s/Muttrc", SYSCONFDIR);
    if (access (buffer, F_OK) == -1)
      snprintf (buffer, sizeof (buffer), "%s/Muttrc-%s", PKGDATADIR, MUTT_VERSION);
    if (access (buffer, F_OK) == -1)
      snprintf (buffer, sizeof (buffer), "%s/Muttrc", PKGDATADIR);
    if (access (buffer, F_OK) != -1)
    {
      if (source_rc (buffer, &err) != 0)
      {
	fputs (err.data, stderr);
	fputc ('\n', stderr);
	need_pause = 1;
      }
    }
  }

  /* Read the user's initialization file.  */
  if (Muttrc)
  {
    if (!option (OPTNOCURSES))
      endwin ();
    if (source_rc (Muttrc, &err) != 0)
    {
      fputs (err.data, stderr);
      fputc ('\n', stderr);
      need_pause = 1;
    }
  }

  if (mutt_execute_commands (commands) != 0)
    need_pause = 1;

  if (need_pause && !option (OPTNOCURSES))
  {
    if (mutt_any_key_to_continue (NULL) == -1)
      mutt_exit(1);
  }

  mutt_read_histfile ();

#if 0
  set_option (OPTWEED); /* turn weeding on by default */
#endif

  FREE (&err.data);
}