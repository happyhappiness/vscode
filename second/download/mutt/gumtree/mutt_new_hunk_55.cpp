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

