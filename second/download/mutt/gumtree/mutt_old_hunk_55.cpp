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

