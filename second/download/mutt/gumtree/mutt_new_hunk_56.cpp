	
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

