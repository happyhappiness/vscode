int main (int argc, char **argv, char **environ)
{
  char folder[_POSIX_PATH_MAX] = "";
  char *subject = NULL;
  char *includeFile = NULL;
  char *draftFile = NULL;
  char *newMagic = NULL;
  HEADER *msg = NULL;
  LIST *attach = NULL;
  LIST *commands = NULL;
  LIST *queries = NULL;
  LIST *alias_queries = NULL;
  int sendflags = 0;
  int flags = 0;
  int version = 0;
  int i;
  int explicit_folder = 0;
  int dump_variables = 0;
  int edit_infile = 0;
  extern char *optarg;
  extern int optind;
  int double_dash = argc, nargc = 1;

  /* sanity check against stupid administrators */
  
  if(getegid() != getgid())
  {
    fprintf(stderr, "%s: I don't want to run with privileges!\n",
	    argv[0]);
    exit(1);
  }

  setlocale (LC_ALL, "");

#ifdef ENABLE_NLS
  /* FIXME what about the LOCALES_HACK in mutt_init() [init.c] ? */
  {
    char *domdir = getenv ("TEXTDOMAINDIR");
    if (domdir && domdir[0])
      bindtextdomain (PACKAGE, domdir);
    else
      bindtextdomain (PACKAGE, MUTTLOCALEDIR);
    textdomain (PACKAGE);
  }
#endif

  mutt_error = mutt_nocurses_error;
  mutt_message = mutt_nocurses_error;
  SRAND (time (NULL));
  umask (077);

  memset (Options, 0, sizeof (Options));
  memset (QuadOptions, 0, sizeof (QuadOptions));

  /* Init envlist */
  {
    char **srcp, **dstp;
    int count = 0;
    for (srcp = environ; srcp && *srcp; srcp++)
      count++;
    envlist = safe_calloc(count+1, sizeof(char *));
    for (srcp = environ, dstp = envlist; srcp && *srcp; srcp++, dstp++)
      *dstp = safe_strdup(*srcp);
  }

  for (optind = 1; optind < double_dash; )
  {
    /* We're getopt'ing POSIXLY, so we'll be here every time getopt()
     * encounters a non-option.  That could be a file to attach 
     * (all non-options between -a and --) or it could be an address
     * (which gets collapsed to the front of argv).
     */
    for (; optind < argc; optind++)
    {
      if (argv[optind][0] == '-' && argv[optind][1] != '\0')
      {
        if (argv[optind][1] == '-' && argv[optind][2] == '\0')
          double_dash = optind; /* quit outer loop after getopt */
        break;                  /* drop through to getopt */
      }

      /* non-option, either an attachment or address */
      if (attach)
        attach = mutt_add_list (attach, argv[optind]);
      else
        argv[nargc++] = argv[optind];
    }

    if ((i = getopt (argc, argv, "+A:a:b:F:f:c:Dd:Ee:H:s:i:hm:npQ:RvxyzZ")) != EOF)
      switch (i)
      {
      case 'A':
        alias_queries = mutt_add_list (alias_queries, optarg);
        break;
      case 'a':
	attach = mutt_add_list (attach, optarg);
	break;

      case 'F':
	mutt_str_replace (&Muttrc, optarg);
	break;

      case 'f':
	strfcpy (folder, optarg, sizeof (folder));
        explicit_folder = 1;
	break;

      case 'b':
      case 'c':
	if (!msg)
	  msg = mutt_new_header ();
	if (!msg->env)
	  msg->env = mutt_new_envelope ();
	if (i == 'b')
	  msg->env->bcc = rfc822_parse_adrlist (msg->env->bcc, optarg);
	else
	  msg->env->cc = rfc822_parse_adrlist (msg->env->cc, optarg);
	break;

      case 'D':
	dump_variables = 1;
	break;

      case 'd':
#ifdef DEBUG
	if (mutt_atoi (optarg, &debuglevel) < 0 || debuglevel <= 0)
	{
	  fprintf (stderr, _("Error: value '%s' is invalid for -d.\n"), optarg);
	  return 1;
	}
	printf (_("Debugging at level %d.\n"), debuglevel);
#else
	printf ("%s", _("DEBUG was not defined during compilation.  Ignored.\n"));
#endif
	break;

      case 'E':
        edit_infile = 1;
        break;

      case 'e':
	commands = mutt_add_list (commands, optarg);
	break;

      case 'H':
	draftFile = optarg;
	break;

      case 'i':
	includeFile = optarg;
	break;

      case 'm':
	/* should take precedence over .muttrc setting, so save it for later */
	newMagic = optarg; 
	break;

      case 'n':
	flags |= MUTT_NOSYSRC;
	break;

      case 'p':
	sendflags |= SENDPOSTPONED;
	break;

      case 'Q':
        queries = mutt_add_list (queries, optarg);
        break;
      
      case 'R':
	flags |= MUTT_RO; /* read-only mode */
	break;

      case 's':
	subject = optarg;
	break;

      case 'v':
	version++;
	break;

      case 'x': /* mailx compatible send mode */
	sendflags |= SENDMAILX;
	break;

      case 'y': /* My special hack mode */
	flags |= MUTT_SELECT;
	break;

      case 'z':
	flags |= MUTT_IGNORE;
	break;

      case 'Z':
	flags |= MUTT_BUFFY | MUTT_IGNORE;
	break;

      default:
	mutt_usage ();
      }
  }

  /* collapse remaining argv */
  while (optind < argc)
    argv[nargc++] = argv[optind++];
  optind = 1;
  argc = nargc;

  switch (version)
  {
    case 0:
      break;
    case 1:
      show_version ();
      break;
    default:
      puts (mutt_make_version ());
      puts (_(Copyright));
      puts (_(Licence));
      puts (_(Obtaining));
      puts (_(ReachingUs));
      exit (0);
  }

  /* Check for a batch send. */
  if (!isatty (0) || queries || alias_queries || dump_variables)
  {
    set_option (OPTNOCURSES);
    sendflags = SENDBATCH;
  }

  /* Always create the mutt_windows because batch mode has some shared code
   * paths that end up referencing them. */
  mutt_init_windows ();

  /* This must come before mutt_init() because curses needs to be started
     before calling the init_pair() function to set the color scheme.  */
  if (!option (OPTNOCURSES))
  {
    start_curses ();

    /* check whether terminal status is supported (must follow curses init) */
    TSSupported = mutt_ts_capability();
  }

  /* set defaults and read init files */
  mutt_init (flags & MUTT_NOSYSRC, commands);
  mutt_free_list (&commands);

  /* Initialize crypto backends.  */
  crypt_init ();

  if (newMagic)
    mx_set_magic (newMagic);

  if (queries)
  {
    for (; optind < argc; optind++)
      queries = mutt_add_list (queries, argv[optind]);
    return mutt_query_variables (queries);
  }
  if (dump_variables)
    return mutt_dump_variables();

  if (alias_queries)
  {
    int rv = 0;
    ADDRESS *a;
    for (; optind < argc; optind++)
      alias_queries = mutt_add_list (alias_queries, argv[optind]);
    for (; alias_queries; alias_queries = alias_queries->next)
    {
      if ((a = mutt_lookup_alias (alias_queries->data)))
      {	
	/* output in machine-readable form */
	mutt_addrlist_to_intl (a, NULL);
	mutt_write_address_list (a, stdout, 0, 0);
      }
      else
      {
	rv = 1;
	printf ("%s\n", alias_queries->data);
      }
    }
    return rv;
  }

  if (!option (OPTNOCURSES))
  {
    SETCOLOR (MT_COLOR_NORMAL);
    clear ();
    mutt_error = mutt_curses_error;
    mutt_message = mutt_curses_message;
  }

  /* Create the Maildir directory if it doesn't exist. */
  if (!option (OPTNOCURSES) && Maildir)
  {
    struct stat sb;
    char fpath[_POSIX_PATH_MAX];
    char msg[STRING];

    strfcpy (fpath, Maildir, sizeof (fpath));
    mutt_expand_path (fpath, sizeof (fpath));
#ifdef USE_IMAP
    /* we're not connected yet - skip mail folder creation */
    if (!mx_is_imap (fpath))
#endif
    if (stat (fpath, &sb) == -1 && errno == ENOENT)
    {
      snprintf (msg, sizeof (msg), _("%s does not exist. Create it?"), Maildir);
      if (mutt_yesorno (msg, MUTT_YES) == MUTT_YES)
      {
	if (mkdir (fpath, 0700) == -1 && errno != EEXIST)
	  mutt_error ( _("Can't create %s: %s."), Maildir, strerror (errno));
      }
    }
  }

  if (sendflags & SENDPOSTPONED)
  {
    if (!option (OPTNOCURSES))
      mutt_flushinp ();
    ci_send_message (SENDPOSTPONED, NULL, NULL, NULL, NULL);
    mutt_free_windows ();
    mutt_endwin (NULL);
  }
  else if (subject || msg || sendflags || draftFile || includeFile || attach ||
	   optind < argc)
  {
    FILE *fin = NULL;
    FILE *fout = NULL;
    char buf[LONG_STRING];
    char *tempfile = NULL, *infile = NULL;
    char *bodytext = NULL, *bodyfile = NULL;
    int rv = 0;
    char expanded_infile[_POSIX_PATH_MAX];
    
    if (!option (OPTNOCURSES))
      mutt_flushinp ();

    if (!msg)
      msg = mutt_new_header ();
    if (!msg->env)
      msg->env = mutt_new_envelope ();

    for (i = optind; i < argc; i++)
    {
      if (url_check_scheme (argv[i]) == U_MAILTO)
      {
        if (url_parse_mailto (msg->env, &bodytext, argv[i]) < 0)
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          fputs (_("Failed to parse mailto: link\n"), stderr);
          exit (1);
        }
      }
      else
        msg->env->to = rfc822_parse_adrlist (msg->env->to, argv[i]);
    }

    if (!draftFile && option (OPTAUTOEDIT) && !msg->env->to && !msg->env->cc)
    {
      if (!option (OPTNOCURSES))
        mutt_endwin (NULL);
      fputs (_("No recipients specified.\n"), stderr);
      exit (1);
    }

    if (subject)
      msg->env->subject = safe_strdup (subject);

    if (draftFile)
    {
      infile = draftFile;
      includeFile = NULL;
    }
    else if (includeFile)
      infile = includeFile;
    else
      edit_infile = 0;

    if (infile || bodytext)
    {
      /* Prepare fin and expanded_infile. */
      if (infile)
      {
	if (mutt_strcmp ("-", infile) == 0)
        {
          if (edit_infile)
          {
            fputs (_("Cannot use -E flag with stdin\n"), stderr);
            exit (1);
          }
	  fin = stdin;
        }
	else
	{
	  strfcpy (expanded_infile, infile, sizeof (expanded_infile));
	  mutt_expand_path (expanded_infile, sizeof (expanded_infile));
	  if ((fin = fopen (expanded_infile, "r")) == NULL)
	  {
	    if (!option (OPTNOCURSES))
	      mutt_endwin (NULL);
	    perror (expanded_infile);
	    exit (1);
	  }
	}
      }

      /* Copy input to a tempfile, and re-point fin to the tempfile.
       * Note: stdin is always copied to a tempfile, ensuring draftFile
       * can stat and get the correct st_size below.
       */
      if (!edit_infile)
      {
        mutt_mktemp (buf, sizeof (buf));
        tempfile = safe_strdup (buf);

        if ((fout = safe_fopen (tempfile, "w")) == NULL)
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          perror (tempfile);
          safe_fclose (&fin);
          FREE (&tempfile);
          exit (1);
        }
        if (fin)
        {
          mutt_copy_stream (fin, fout);
          if (fin != stdin)
            safe_fclose (&fin);
        }
        else if (bodytext)
          fputs (bodytext, fout);
        safe_fclose (&fout);

        if ((fin = fopen (tempfile, "r")) == NULL)
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          perror (tempfile);
          FREE (&tempfile);
          exit (1);
        }
      }
      /* If editing the infile, keep it around afterwards so
       * it doesn't get unlinked, and we can rebuild the draftFile
       */
      else
        sendflags |= SENDNOFREEHEADER;

      /* Parse the draftFile into the full HEADER/BODY structure.
       * Set SENDDRAFTFILE so ci_send_message doesn't overwrite
       * our msg->content.
       */
      if (draftFile)
      {
        HEADER *context_hdr = NULL;
        ENVELOPE *opts_env = msg->env;
        struct stat st;
        LIST *uh, **last_uhp;

        sendflags |= SENDDRAFTFILE;

        /* Set up a "context" header with just enough information so that
         * mutt_prepare_template() can parse the message in fin.
         */
        context_hdr = mutt_new_header ();
        context_hdr->offset = 0;
        context_hdr->content = mutt_new_body ();
        if (fstat (fileno (fin), &st))
        {
          perror (draftFile);
          exit (1);
        }
        context_hdr->content->length = st.st_size;

        mutt_prepare_template (fin, NULL, msg, context_hdr, 0);

        /* Scan for mutt header to set OPTRESUMEDRAFTFILES */
        for (last_uhp = &msg->env->userhdrs, uh = *last_uhp;
             uh; uh = *last_uhp)
        {
          if (ascii_strncasecmp ("X-Mutt-Resume-Draft:", uh->data, 20) == 0)
          {
            if (option (OPTRESUMEEDITEDDRAFTFILES))
              set_option (OPTRESUMEDRAFTFILES);

            *last_uhp = uh->next;
            uh->next = NULL;
            mutt_free_list (&uh);
          }
          else
            last_uhp = &uh->next;
        }

        rfc822_append (&msg->env->to, opts_env->to, 0);
        rfc822_append (&msg->env->cc, opts_env->cc, 0);
        rfc822_append (&msg->env->bcc, opts_env->bcc, 0);
        if (opts_env->subject)
          mutt_str_replace (&msg->env->subject, opts_env->subject);

        mutt_free_envelope (&opts_env);
        mutt_free_header (&context_hdr);
      }
      /* Editing the includeFile: pass it directly in.
       * Note that SENDNOFREEHEADER is set above so it isn't unlinked.
       */
      else if (edit_infile)
        bodyfile = expanded_infile;
      /* For bodytext and unedited includeFile: use the tempfile.
       */
      else
        bodyfile = tempfile;

      if (fin)
        safe_fclose (&fin);
    }

    FREE (&bodytext);

    if (attach)
    {
      LIST *t = attach;
      BODY *a = msg->content;

      while (a && a->next)
        a = a->next;

      while (t)
      {
	if (a)
	{
	  a->next = mutt_make_file_attach (t->data);
	  a = a->next;
	}
	else
	  msg->content = a = mutt_make_file_attach (t->data);
	if (!a)
	{
	  if (!option (OPTNOCURSES))
	    mutt_endwin (NULL);
	  fprintf (stderr, _("%s: unable to attach file.\n"), t->data);
	  mutt_free_list (&attach);
	  exit (1);
	}
	t = t->next;
      }
      mutt_free_list (&attach);
    }

    rv = ci_send_message (sendflags, msg, bodyfile, NULL, NULL);

    if (edit_infile)
    {
      if (includeFile)
        msg->content->unlink = 0;
      else if (draftFile)
      {
        if (truncate (expanded_infile, 0) == -1)
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          perror (expanded_infile);
          exit (1);
        }
        if ((fout = safe_fopen (expanded_infile, "a")) == NULL)
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          perror (expanded_infile);
          exit (1);
        }

        /* If the message was sent or postponed, these will already
         * have been done.
         */
        if (rv < 0)
        {
          if (msg->content->next)
            msg->content = mutt_make_multipart (msg->content);
          mutt_encode_descriptions (msg->content, 1);
          mutt_prepare_envelope (msg->env, 0);
          mutt_env_to_intl (msg->env, NULL, NULL);
        }

        mutt_write_rfc822_header (fout, msg->env, msg->content, -1, 0);
        if (option (OPTRESUMEEDITEDDRAFTFILES))
          fprintf (fout, "X-Mutt-Resume-Draft: 1\n");
        fputc ('\n', fout);
        if ((mutt_write_mime_body (msg->content, fout) == -1))
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          safe_fclose (&fout);
          exit (1);
        }
        safe_fclose (&fout);
      }

      mutt_free_header (&msg);
    }

    /* !edit_infile && draftFile will leave the tempfile around */
    if (tempfile)
    {
      unlink (tempfile);
      FREE (&tempfile);
    }

    mutt_free_windows ();
    if (!option (OPTNOCURSES))
      mutt_endwin (NULL);

    if (rv)
      exit(1);
  }
  else
  {
    if (flags & MUTT_BUFFY)
    {
      if (!mutt_buffy_check (0))
      {
	mutt_endwin _("No mailbox with new mail.");
	exit (1);
      }
      folder[0] = 0;
      mutt_buffy (folder, sizeof (folder));
    }
    else if (flags & MUTT_SELECT)
    {
      if (!Incoming) {
	mutt_endwin _("No incoming mailboxes defined.");
	exit (1);
      }
      folder[0] = 0;
      mutt_select_file (folder, sizeof (folder), MUTT_SEL_FOLDER | MUTT_SEL_BUFFY);
      if (!folder[0])
      {
	mutt_endwin (NULL);
	exit (0);
      }
    }

    if (!folder[0])
      strfcpy (folder, NONULL(Spoolfile), sizeof (folder));
    mutt_expand_path (folder, sizeof (folder));

    mutt_str_replace (&CurrentFolder, folder);
    mutt_str_replace (&LastFolder, folder);

    if (flags & MUTT_IGNORE)
    {
      /* check to see if there are any messages in the folder */
      switch (mx_check_empty (folder))
      {
	case -1:
	  mutt_endwin (strerror (errno));
	  exit (1);
	case 1:
	  mutt_endwin _("Mailbox is empty.");
	  exit (1);
      }
    }

    mutt_folder_hook (folder);

    if((Context = mx_open_mailbox (folder, ((flags & MUTT_RO) || option (OPTREADONLY)) ? MUTT_READONLY : 0, NULL))
       || !explicit_folder)
    {
#ifdef USE_SIDEBAR
      mutt_sb_set_open_buffy ();
#endif
      mutt_index_menu ();
      if (Context)
	FREE (&Context);
    }
#ifdef USE_IMAP
    imap_logout_all ();
#endif
#ifdef USE_SASL
    mutt_sasl_done ();
#endif
    mutt_free_opts ();
    mutt_free_windows ();
    mutt_endwin (Errorbuf);
  }

  exit (0);
}