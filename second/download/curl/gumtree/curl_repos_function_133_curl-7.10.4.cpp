void Curl_SSL_init(void)
{
#ifdef USE_SSLEAY
  /* make sure this is only done once */
  if(0 != init_ssl)
    return;

  init_ssl++; /* never again */

#ifdef HAVE_ENGINE_LOAD_BUILTIN_ENGINES
  ENGINE_load_builtin_engines();
#endif

  /* Lets get nice error messages */
  SSL_load_error_strings();

  /* Setup all the global SSL stuff */
  SSLeay_add_ssl_algorithms();
#else
  /* SSL disabled, do nothing */
#endif
}