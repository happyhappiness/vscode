static int Curl_qsossl_close_one(struct ssl_connect_data * conn,
                                 struct SessionHandle * data)

{
  int rc;

  if(!conn->handle)
    return 0;

  rc = SSL_Destroy(conn->handle);

  if(rc) {
    if(rc == SSL_ERROR_IO) {
      failf(data, "SSL_Destroy() I/O error: %s", strerror(errno));
      return -1;
    }

    /* An SSL error. */
    failf(data, "SSL_Destroy() returned error %s", SSL_Strerror(rc, NULL));
    return -1;
  }

  conn->handle = NULL;
  return 0;
}