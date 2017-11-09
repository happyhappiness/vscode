static bool Curl_darwinssl_data_pending(const struct connectdata *conn,
                                        int connindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[connindex];
  OSStatus err;
  size_t buffer;

  if(BACKEND->ssl_ctx) {  /* SSL is in use */
    err = SSLGetBufferedReadSize(BACKEND->ssl_ctx, &buffer);
    if(err == noErr)
      return buffer > 0UL;
    return false;
  }
  else
    return false;
}