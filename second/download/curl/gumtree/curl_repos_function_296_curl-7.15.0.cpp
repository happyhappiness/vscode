int Curl_ossl_init(void)
{
#ifdef HAVE_ENGINE_LOAD_BUILTIN_ENGINES
  ENGINE_load_builtin_engines();
#endif

  /* Lets get nice error messages */
  SSL_load_error_strings();

  /* Setup all the global SSL stuff */
  if (!SSLeay_add_ssl_algorithms())
    return 0;

  return 1;
}