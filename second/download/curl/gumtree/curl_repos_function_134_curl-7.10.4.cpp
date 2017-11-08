void Curl_SSL_cleanup(void)
{
#ifdef USE_SSLEAY
  if(init_ssl) {
    /* only cleanup if we did a previous init */

    /* Free the SSL error strings */
    ERR_free_strings();
  
    /* EVP_cleanup() removes all ciphers and digests from the
       table. */
    EVP_cleanup();

#ifdef HAVE_ENGINE_cleanup
    ENGINE_cleanup();
#endif

    init_ssl=0; /* not inited any more */
  }
#else
  /* SSL disabled, do nothing */
#endif
}