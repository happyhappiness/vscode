  return CURLE_OK;

}



#ifdef USE_LIBIDN

/*

 * Initialise use of IDNA library.

 * It falls back to ASCII if $CHARSET isn't defined. This doesn't work for

 * idna_to_ascii_lz().

 */

static void idna_init (void)

{

#ifdef WIN32

  char buf[60];

  UINT cp = GetACP();



  if(!getenv("CHARSET") && cp > 0) {

    snprintf(buf, sizeof(buf), "CHARSET=cp%u", cp);

    putenv(buf);

  }

#else

  /* to do? */

#endif

}

#endif  /* USE_LIBIDN */



/* true globals -- for curl_global_init() and curl_global_cleanup() */

static unsigned int  initialized;

static long          init_flags;

