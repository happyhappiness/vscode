CURLcode Curl_addrinfo6_callback(void *arg, /* "struct connectdata *" */
                                 int status,
#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
                                 int timeouts,
#endif
                                 struct addrinfo *ai)
{
 /* NOTE: for CURLRES_ARES, the 'ai' argument is really a
  * 'struct hostent' pointer.
  */
#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
  (void)timeouts; /* ignored */
#endif
  return addrinfo_callback(arg, status, ai);
}