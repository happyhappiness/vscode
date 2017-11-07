int main (int argc, char **argv)
{
  char folder[_POSIX_PATH_MAX] = "";
  char *subject = NULL;
  char *includeFile = NULL;
  char *draftFile = NULL;
  char *newMagic = NULL;
  HEADER *msg = NULL;
  LIST *attach = NULL;
  LIST *commands = NULL;
  int sendflags = 0;
  int flags = 0;
  int version = 0;
  int i;
  int explicit_folder = 0;
  extern char *optarg;
  extern int optind;

  /* sanity check against stupid administrators */
  
  if(getegid() != getgid())
  {
    fprintf(stderr, "%s: I don't want to run with privileges!\n",
	    argv[0]);
    exit(1);
  }

#ifdef ENABLE_NLS
  /* FIXME what about init.c:1439 ? */
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, MUTTLOCALEDIR);
  textdomain (PACKAGE);
#endif

  setlocale (LC_CTYPE, "");

  mutt_error = mutt_nocurses_error;
  mutt_message = mutt_nocurses_error;
  SRAND (time (NULL));
  umask (077);

  memset (Options, 0, sizeof (Options));
  memset (QuadOptions, 0, sizeof (QuadOptions));
  
  while ((i = getopt (argc, argv, "a:b:F:f:c:d:e:H:s:i:hm:npRvxyzZ")) != EOF)
    switch (i)
    {
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

      case 'd':
#ifdef DEBUG
	debuglevel = atoi (optarg);
	printf (_("Debugging at level %d.\n"), debuglevel);
#else
	printf _("DEBUG was not defined during compilation.  Ignored.\n");
#endif
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
	flags |= M_NOSYSRC;
	break;

      case 'p':
	sendflags |= SENDPOSTPONED;
	break;

      case 'R':
	flags |= M_RO; /* read-only mode */
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
	flags |= M_SELECT;
	break;

      case 'z':
	flags |= M_IGNORE;
	break;

      case 'Z':
	flags |= M_BUFFY | M_IGNORE;
	break;

      default:
	mutt_usage ();
    }

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
      puts (_(ReachingUs));
      exit (0);
  }

  /* Check for a batch send. */
  if (!isatty (0))
  {
    set_option (OPTNOCURSES);
    sendflags = SENDBATCH;
  }

  /* This must come before mutt_init() because curses needs to be started
     before calling the init_pair() function to set the color scheme.  */
  if (!option (OPTNOCURSES))
    start_curses ();

  /* set defaults and read init files */
  mutt_init (flags & M_NOSYSRC, commands);
  mutt_free_list (&commands);

  if (newMagic)
    mx_set_magic (newMagic);

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
      if (mutt_yesorno (msg, 1) == 1)
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
    mutt_endwin (NULL);
  }
  else if (subject || msg || sendflags || draftFile || includeFile || attach ||
	   optind < argc)
  {
    FILE *fin = NULL;
    char buf[LONG_STRING];
    char *tempfile = NULL, *infile = NULL;
    char *bodytext = NULL;
    
    if (!option (OPTNOCURSES))
      mutt_flushinp ();

    if (!msg)
      msg = mutt_new_header ();

    if (draftFile)
      infile = draftFile;
    else
    {
      if (!msg->env)
	msg->env = mutt_new_envelope ();

      for (i = optind; i < argc; i++)
      {
	if (url_check_scheme (argv[i]) == U_MAILTO)
	  url_parse_mailto (msg->env, &bodytext, argv[i]);
	else
	  msg->env->to = rfc822_parse_adrlist (msg->env->to, argv[i]);
      }

      if (option (OPTAUTOEDIT) && !msg->env->to && !msg->env->cc)
      {
	if (!option (OPTNOCURSES))
	  mutt_endwin (NULL);
	fputs (_("No recipients specified.\n"), stderr);
	exit (1);
      }

      if (subject)
	msg->env->subject = safe_strdup (subject);

      if (includeFile)
	infile = includeFile;
    }

    if (infile || bodytext)
    {
      if (infile)
      {
	if (mutt_strcmp ("-", infile) == 0)
	  fin = stdin;
	else 
	{
	  char path[_POSIX_PATH_MAX];
	  
	  strfcpy (path, infile, sizeof (path));
	  mutt_expand_path (path, sizeof (path));
	  if ((fin = fopen (path, "r")) == NULL)
	  {
	    if (!option (OPTNOCURSES))
	      mutt_endwin (NULL);
	    perror (path);
	    exit (1);
	  }
	}
      }
      else
	fin = NULL;

      mutt_mktemp (buf);
      tempfile = safe_strdup (buf);

      if (draftFile)
	msg->env = mutt_read_rfc822_header (fin, NULL, 1, 0);

      /* is the following if still needed? */
      
      if (tempfile)
      {
	FILE *fout;

	if ((fout = safe_fopen (tempfile, "w")) == NULL)
	{
	  if (!option (OPTNOCURSES))
	    mutt_endwin (NULL);
	  perror (tempfile);
	  fclose (fin);
	  FREE (&tempfile);
	  exit (1);
	}
	if (fin)
	  mutt_copy_stream (fin, fout);
	else if (bodytext)
	  fputs (bodytext, fout);
	fclose (fout);
	if (fin && fin != stdin)
	  fclose (fin);
      }
    }

    safe_free ((void **) &bodytext);
    
    if (attach)
    {
      LIST *t = attach;
      BODY *a = NULL;

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

    ci_send_message (sendflags, msg, tempfile, NULL, NULL);

    if (!option (OPTNOCURSES))
      mutt_endwin (NULL);
  }
  else
  {
    if (flags & M_BUFFY)
    {
      if (!mutt_buffy_check (0))
      {
	mutt_endwin _("No mailbox with new mail.");
	exit (1);
      }
      folder[0] = 0;
      mutt_buffy (folder, sizeof (folder));
    }
    else if (flags & M_SELECT)
    {
      if (!Incoming) {
	mutt_endwin _("No incoming mailboxes defined.");
	exit (1);
      }
      folder[0] = 0;
      mutt_select_file (folder, sizeof (folder), M_SEL_FOLDER | M_SEL_BUFFY);
      if (!folder[0])
      {
	mutt_endwin (NULL);
	exit (0);
      }
    }

    if (!folder[0])
      strfcpy (folder, NONULL(Spoolfile), sizeof (folder));
    mutt_expand_path (folder, sizeof (folder));

    mutt_str_replace (&LastFolder, folder);

    if (flags & M_IGNORE)
    {
      struct stat st;

      /* check to see if there are any messages in the folder */
      if (stat (folder, &st) != 0)
      {
	mutt_endwin (strerror (errno));
	exit (1);
      }

      if (st.st_size == 0)
      {
	mutt_endwin _("Mailbox is empty.");
	exit (1);
      }
    }

    mutt_folder_hook (folder);

    if((Context = mx_open_mailbox (folder, ((flags & M_RO) || option (OPTREADONLY)) ? M_READONLY : 0, NULL))
       || !explicit_folder)
    {
      mutt_index_menu ();
      if (Context)
	safe_free ((void **)&Context);
    }
    mutt_endwin (Errorbuf);
  }

  exit (0);
}