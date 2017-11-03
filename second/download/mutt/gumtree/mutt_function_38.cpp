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
  printf ("\nncurses: %s (compiled with %s)", curses_version(), NCURSES_VERSION);
#elif defined(USE_SLANG_CURSES)
  printf ("\nslang: %d", SLANG_VERSION);
#endif

#ifdef _LIBICONV_VERSION
  printf ("\nlibiconv: %d.%d", _LIBICONV_VERSION >> 8,
	  _LIBICONV_VERSION & 0xff);
#endif

#ifdef HAVE_LIBIDN
  printf ("\nlibidn: %s (compiled with %s)", stringprep_check_version (NULL), 
	  STRINGPREP_VERSION);
#endif

#ifdef USE_HCACHE
  printf ("\nhcache backend: %s", mutt_hcache_backend ());
#endif

  puts ("\n\nCompiler:");
  rstrip_in_place((char *)cc_version);
  puts (cc_version);

  rstrip_in_place((char *)configure_options);
  printf ("\nConfigure options: %s\n", configure_options);

  rstrip_in_place((char *)cc_cflags);
  printf ("\nCompilation CFLAGS: %s\n", cc_cflags);

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

#ifdef USE_FCNTL
	"+USE_FCNTL  "
#else
	"-USE_FCNTL  "
#endif

#ifdef USE_FLOCK
	"+USE_FLOCK   "
#else
	"-USE_FLOCK   "
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

#ifdef USE_SMTP
	"+USE_SMTP  "
#else
	"-USE_SMTP  "
#endif
	"\n"
	
#ifdef USE_SSL_OPENSSL
	"+USE_SSL_OPENSSL  "
#else
	"-USE_SSL_OPENSSL  "
#endif

#ifdef USE_SSL_GNUTLS
	"+USE_SSL_GNUTLS  "
#else
	"-USE_SSL_GNUTLS  "
#endif

#ifdef USE_SASL
	"+USE_SASL  "
#else
	"-USE_SASL  "
#endif
#ifdef USE_GSS
	"+USE_GSS  "
#else
	"-USE_GSS  "
#endif

#if HAVE_GETADDRINFO
	"+HAVE_GETADDRINFO  "
#else
	"-HAVE_GETADDRINFO  "
#endif
        );
  	
  puts (
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
#ifdef CRYPT_BACKEND_CLASSIC_PGP
        "+CRYPT_BACKEND_CLASSIC_PGP  "
#else
        "-CRYPT_BACKEND_CLASSIC_PGP  "
#endif
#ifdef CRYPT_BACKEND_CLASSIC_SMIME
        "+CRYPT_BACKEND_CLASSIC_SMIME  "
#else
        "-CRYPT_BACKEND_CLASSIC_SMIME  "
#endif
#ifdef CRYPT_BACKEND_GPGME
        "+CRYPT_BACKEND_GPGME  "
#else
        "-CRYPT_BACKEND_GPGME  "
#endif
        );
  
  puts (
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

#if HAVE_LIBIDN
	"+HAVE_LIBIDN  "
#else
	"-HAVE_LIBIDN  "
#endif
	
#if HAVE_GETSID
	"+HAVE_GETSID  "
#else
	"-HAVE_GETSID  "
#endif

#if USE_HCACHE
	"+USE_HCACHE  "
#else
	"-USE_HCACHE  "
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