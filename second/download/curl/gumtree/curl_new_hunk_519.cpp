     the same message; but since threadsafeness is not handled here,
     this may occur (and we don't care!). */

  if (testwarn) {
    testwarn = 0;

#ifdef USE_TLS_SRP
    if ((int) STRING_LAST != (int) STRING_TLSAUTH_PASSWORD + 1)
#else
    if ((int) STRING_LAST != (int) STRING_MAIL_FROM + 1)
#endif
      curl_mfprintf(stderr,
       "*** WARNING: curl_easy_setopt_ccsid() should be reworked ***\n");
    }

  data = (struct SessionHandle *) curl;
  va_start(arg, tag);
