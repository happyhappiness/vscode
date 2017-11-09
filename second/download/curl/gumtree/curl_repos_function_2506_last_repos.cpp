static void Curl_darwinssl_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(BACKEND->ssl_ctx) {
    (void)SSLClose(BACKEND->ssl_ctx);
#if CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS
    if(SSLCreateContext != NULL)
      CFRelease(BACKEND->ssl_ctx);
#if CURL_SUPPORT_MAC_10_8
    else
      (void)SSLDisposeContext(BACKEND->ssl_ctx);
#endif  /* CURL_SUPPORT_MAC_10_8 */
#else
    (void)SSLDisposeContext(BACKEND->ssl_ctx);
#endif /* CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS */
    BACKEND->ssl_ctx = NULL;
  }
  BACKEND->ssl_sockfd = 0;
}