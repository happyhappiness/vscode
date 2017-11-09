static void Curl_axtls_session_free(void *ptr)
{
  (void)ptr;
  /* free the ID */
  /* both openssl.c and gtls.c do something here, but axTLS's OpenSSL
     compatibility layer does nothing, so we do nothing too. */
}