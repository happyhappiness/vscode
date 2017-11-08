CURLcode Curl_addrinfo4_callback(void *arg, /* "struct connectdata *" */
                                 int status,
#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
                                 int timeouts,
#endif
                                 struct hostent *hostent)
{
#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
  (void)timeouts; /* ignored */
#endif
  return addrinfo_callback(arg, status, hostent);
}