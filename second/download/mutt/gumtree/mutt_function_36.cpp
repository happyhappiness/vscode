static void show_version (void)
{
  struct utsname uts;

  puts (mutt_make_version());
  puts (_(Notice));

  uname (&uts);

#ifdef _AIX
  printf ("System: %s %s.%s", uts.sysname, uts.version, uts.release);
#elif defined (SCO)
  printf ("System: SCO %s", uts.release);
#else
  printf ("System: %s %s", uts.sysname, uts.release);
#endif

  printf (" (%s)", uts.machine);

#ifdef NCURSES_VERSION
  printf (" [using ncurses %s]", NCURSES_VERSION);
#elif defined(USE_SLANG_CURSES)
  printf (" [using slang %d]", SLANG_VERSION);
#endif

  puts (_("\nCompile options:"));

#ifdef DOMAIN
  printf ("DOMAIN=\"%s\"\n", DOMAIN);
#else
  puts ("-DOMAIN");
#endif

#ifdef DEBUG
  puts ("+DEBUG");
#else
  puts ("-DEBUG");
#endif
  

  
  puts (

#ifdef HOMESPOOL
	"+HOMESPOOL  "
#else
	"-HOMESPOOL  "
#endif

#ifdef USE_SETGID
	"+USE_SETGID  "
#else
	"-USE_SETGID  "
#endif

#ifdef USE_DOTLOCK
	"+USE_DOTLOCK  "
#else
	"-USE_DOTLOCK  "
#endif

#ifdef DL_STANDALONE
	"+DL_STANDALONE  "
#else
	"-DL_STANDALONE  "
#endif

	"\n"
	
#ifdef USE_FCNTL
	"+USE_FCNTL  "
#else
	"-USE_FCNTL  "
#endif

#ifdef USE_FLOCK
	"+USE_FLOCK"
#else
	"-USE_FLOCK"
#endif
	);
  puts (
#ifdef USE_POP
	"+USE_POP  "
#else
	"-USE_POP  "
#endif

#ifdef USE_IMAP
        "+USE_IMAP  "
#else
        "-USE_IMAP  "
#endif

#ifdef USE_GSS
	"+USE_GSS  "
#else
	"-USE_GSS  "
#endif

	
#ifdef USE_SSL
	"+USE_SSL  "
#else
	"-USE_SSL  "
#endif

#ifdef USE_SASL
	"+USE_SASL  "
#else
	"-USE_SASL  "
#endif
	"\n"
	
#ifdef HAVE_REGCOMP
	"+HAVE_REGCOMP  "
#else
	"-HAVE_REGCOMP  "
#endif

#ifdef USE_GNU_REGEX
	"+USE_GNU_REGEX  "
#else
	"-USE_GNU_REGEX  "
#endif

	"\n"
	
#ifdef HAVE_COLOR
	"+HAVE_COLOR  "
#else
	"-HAVE_COLOR  "
#endif
	
#ifdef HAVE_START_COLOR
	"+HAVE_START_COLOR  "
#else
	"-HAVE_START_COLOR  "
#endif
	
#ifdef HAVE_TYPEAHEAD
	"+HAVE_TYPEAHEAD  "
#else
	"-HAVE_TYPEAHEAD  "
#endif
	
#ifdef HAVE_BKGDSET
	"+HAVE_BKGDSET  "
#else
	"-HAVE_BKGDSET  "
#endif

	"\n"
	
#ifdef HAVE_CURS_SET
	"+HAVE_CURS_SET  "
#else
	"-HAVE_CURS_SET  "
#endif
	
#ifdef HAVE_META
	"+HAVE_META  "
#else
	"-HAVE_META  "
#endif
	
#ifdef HAVE_RESIZETERM
	"+HAVE_RESIZETERM  "
#else
	"-HAVE_RESIZETERM  "
#endif
	
	
	);
  
  
  puts (
	
#ifdef HAVE_PGP
	"+HAVE_PGP  "
#else
	"-HAVE_PGP  "
#endif

#ifdef BUFFY_SIZE
	"+BUFFY_SIZE "
#else
	"-BUFFY_SIZE "
#endif
#ifdef EXACT_ADDRESS
	"+EXACT_ADDRESS  "
#else
	"-EXACT_ADDRESS  "
#endif

#ifdef SUN_ATTACHMENT
	"+SUN_ATTACHMENT  "
#else
	"-SUN_ATTACHMENT  "
#endif

	"\n"
	
#ifdef ENABLE_NLS
	"+ENABLE_NLS  "
#else
	"-ENABLE_NLS  "
#endif

#ifdef LOCALES_HACK
	"+LOCALES_HACK  "
#else
	"-LOCALES_HACK  "
#endif
	      
#ifdef HAVE_WC_FUNCS
	"+HAVE_WC_FUNCS  "
#else
	"-HAVE_WC_FUNCS  "
#endif
	
#ifdef HAVE_LANGINFO_CODESET
	"+HAVE_LANGINFO_CODESET  "
#else
	"-HAVE_LANGINFO_CODESET  "
#endif

	
#ifdef HAVE_LANGINFO_YESEXPR
 	"+HAVE_LANGINFO_YESEXPR  "
#else
 	"-HAVE_LANGINFO_YESEXPR  "
#endif
	
	"\n"

#if HAVE_ICONV
	"+HAVE_ICONV  "
#else
	"-HAVE_ICONV  "
#endif

#if ICONV_NONTRANS
	"+ICONV_NONTRANS  "
#else
	"-ICONV_NONTRANS  "
#endif

#if HAVE_GETSID
	"+HAVE_GETSID  "
#else
	"-HAVE_GETSID  "
#endif

#if HAVE_GETADDRINFO
	"+HAVE_GETADDRINFO  "
#else
	"-HAVE_GETADDRINFO  "
#endif

	);

#ifdef ISPELL
  printf ("ISPELL=\"%s\"\n", ISPELL);
#else
  puts ("-ISPELL");
#endif

  printf ("SENDMAIL=\"%s\"\n", SENDMAIL);
  printf ("MAILPATH=\"%s\"\n", MAILPATH);
  printf ("PKGDATADIR=\"%s\"\n", PKGDATADIR);
  printf ("SYSCONFDIR=\"%s\"\n", SYSCONFDIR);
  printf ("EXECSHELL=\"%s\"\n", EXECSHELL);
#ifdef MIXMASTER
  printf ("MIXMASTER=\"%s\"\n", MIXMASTER);
#else
  puts ("-MIXMASTER");
#endif

  puts(_(ReachingUs));

  mutt_print_patchlist();
  
  exit (0);
}