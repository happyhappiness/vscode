void Curl_ossl_cleanup(void)
{
  /* Free the SSL error strings */
  ERR_free_strings();

  /* EVP_cleanup() removes all ciphers and digests from the
     table. */
  EVP_cleanup();

#ifdef HAVE_ENGINE_cleanup
  ENGINE_cleanup();
#endif

#ifdef HAVE_CRYPTO_CLEANUP_ALL_EX_DATA
  /* this function was not present in 0.9.6b, but was added sometimes
     later */
  CRYPTO_cleanup_all_ex_data();
#endif
}