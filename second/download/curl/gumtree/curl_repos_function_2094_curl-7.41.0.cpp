void Curl_ossl_cleanup(void)
{
  /* Free ciphers and digests lists */
  EVP_cleanup();

#ifdef HAVE_ENGINE_CLEANUP
  /* Free engine list */
  ENGINE_cleanup();
#endif

#ifdef HAVE_CRYPTO_CLEANUP_ALL_EX_DATA
  /* Free OpenSSL ex_data table */
  CRYPTO_cleanup_all_ex_data();
#endif

  /* Free OpenSSL error strings */
  ERR_free_strings();

  /* Free thread local error state, destroying hash upon zero refcount */
#ifdef HAVE_ERR_REMOVE_THREAD_STATE
  ERR_remove_thread_state(NULL);
#else
  ERR_remove_state(0);
#endif
}