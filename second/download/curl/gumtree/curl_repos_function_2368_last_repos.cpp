static void Curl_ossl_cleanup(void)
{
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && \
    !defined(LIBRESSL_VERSION_NUMBER)
  /* OpenSSL 1.1 deprecates all these cleanup functions and
     turns them into no-ops in OpenSSL 1.0 compatibility mode */
#else
  /* Free ciphers and digests lists */
  EVP_cleanup();

#ifdef HAVE_ENGINE_CLEANUP
  /* Free engine list */
  ENGINE_cleanup();
#endif

  /* Free OpenSSL error strings */
  ERR_free_strings();

  /* Free thread local error state, destroying hash upon zero refcount */
#ifdef HAVE_ERR_REMOVE_THREAD_STATE
  ERR_remove_thread_state(NULL);
#else
  ERR_remove_state(0);
#endif

  /* Free all memory allocated by all configuration modules */
  CONF_modules_free();

#ifdef HAVE_SSL_COMP_FREE_COMPRESSION_METHODS
  SSL_COMP_free_compression_methods();
#endif
#endif

#ifdef ENABLE_SSLKEYLOGFILE
  if(keylog_file_fp) {
    fclose(keylog_file_fp);
    keylog_file_fp = NULL;
  }
#endif
}