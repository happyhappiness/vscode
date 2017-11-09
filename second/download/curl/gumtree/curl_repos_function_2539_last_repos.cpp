static CURLcode connect_prep(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct Curl_easy *data = conn->data;
  SSL_CTX *ssl_ctx;
  SSL *ssl = NULL;
  int cert_types[] = {SSL_OBJ_X509_CERT, SSL_OBJ_PKCS12, 0};
  int key_types[] = {SSL_OBJ_RSA_KEY, SSL_OBJ_PKCS8, SSL_OBJ_PKCS12, 0};
  int i, ssl_fcn_return;

  /* Assuming users will not compile in custom key/cert to axTLS.
  *  Also, even for blocking connects, use axTLS non-blocking feature.
  */
  uint32_t client_option = SSL_NO_DEFAULT_KEY |
    SSL_SERVER_VERIFY_LATER |
    SSL_CONNECT_IN_PARTS;

  if(connssl->state == ssl_connection_complete)
    /* to make us tolerant against being called more than once for the
       same connection */
    return CURLE_OK;

  if(SSL_CONN_CONFIG(version_max) != CURL_SSLVERSION_MAX_NONE) {
    failf(data, "axtls does not support CURL_SSLVERSION_MAX");
    return CURLE_SSL_CONNECT_ERROR;
  }


  /* axTLS only supports TLSv1 */
  /* check to see if we've been told to use an explicit SSL/TLS version */
  switch(SSL_CONN_CONFIG(version)) {
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    break;
  default:
    failf(data, "axTLS only supports TLS 1.0 and 1.1, "
          "and it cannot be specified which one to use");
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef  AXTLSDEBUG
  client_option |= SSL_DISPLAY_STATES | SSL_DISPLAY_RSA | SSL_DISPLAY_CERTS;
#endif /* AXTLSDEBUG */

  /* Allocate an SSL_CTX struct */
  ssl_ctx = ssl_ctx_new(client_option, SSL_DEFAULT_CLNT_SESS);
  if(ssl_ctx == NULL) {
    failf(data, "unable to create client SSL context");
    return CURLE_SSL_CONNECT_ERROR;
  }

  BACKEND->ssl_ctx = ssl_ctx;
  BACKEND->ssl = NULL;

  /* Load the trusted CA cert bundle file */
  if(SSL_CONN_CONFIG(CAfile)) {
    if(ssl_obj_load(ssl_ctx, SSL_OBJ_X509_CACERT,
                    SSL_CONN_CONFIG(CAfile), NULL) != SSL_OK) {
      infof(data, "error reading ca cert file %s \n",
            SSL_CONN_CONFIG(CAfile));
      if(SSL_CONN_CONFIG(verifypeer)) {
        return CURLE_SSL_CACERT_BADFILE;
      }
    }
    else
      infof(data, "found certificates in %s\n", SSL_CONN_CONFIG(CAfile));
  }

  /* gtls.c tasks we're skipping for now:
   * 1) certificate revocation list checking
   * 2) dns name assignment to host
   * 3) set protocol priority.  axTLS is TLSv1 only, so can probably ignore
   * 4) set certificate priority.  axTLS ignores type and sends certs in
   *  order added.  can probably ignore this.
   */

  /* Load client certificate */
  if(SSL_SET_OPTION(cert)) {
    i = 0;
    /* Instead of trying to analyze cert type here, let axTLS try them all. */
    while(cert_types[i] != 0) {
      ssl_fcn_return = ssl_obj_load(ssl_ctx, cert_types[i],
                                    SSL_SET_OPTION(cert), NULL);
      if(ssl_fcn_return == SSL_OK) {
        infof(data, "successfully read cert file %s \n",
              SSL_SET_OPTION(cert));
        break;
      }
      i++;
    }
    /* Tried all cert types, none worked. */
    if(cert_types[i] == 0) {
      failf(data, "%s is not x509 or pkcs12 format",
            SSL_SET_OPTION(cert));
      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load client key.
     If a pkcs12 file successfully loaded a cert, then there's nothing to do
     because the key has already been loaded. */
  if(SSL_SET_OPTION(key) && cert_types[i] != SSL_OBJ_PKCS12) {
    i = 0;
    /* Instead of trying to analyze key type here, let axTLS try them all. */
    while(key_types[i] != 0) {
      ssl_fcn_return = ssl_obj_load(ssl_ctx, key_types[i],
                                    SSL_SET_OPTION(key), NULL);
      if(ssl_fcn_return == SSL_OK) {
        infof(data, "successfully read key file %s \n",
              SSL_SET_OPTION(key));
        break;
      }
      i++;
    }
    /* Tried all key types, none worked. */
    if(key_types[i] == 0) {
      failf(data, "Failure: %s is not a supported key file",
            SSL_SET_OPTION(key));
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  /* gtls.c does more here that is being left out for now
   * 1) set session credentials.  can probably ignore since axtls puts this
   *    info in the ssl_ctx struct
   * 2) setting up callbacks.  these seem gnutls specific
   */

  if(SSL_SET_OPTION(primary.sessionid)) {
    const uint8_t *ssl_sessionid;
    size_t ssl_idsize;

    /* In axTLS, handshaking happens inside ssl_client_new. */
    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, (void **) &ssl_sessionid, &ssl_idsize,
                              sockindex)) {
      /* we got a session id, use it! */
      infof(data, "SSL re-using session ID\n");
      ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex],
                           ssl_sessionid, (uint8_t)ssl_idsize, NULL);
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  if(!ssl)
    ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex], NULL, 0, NULL);

  BACKEND->ssl = ssl;
  return CURLE_OK;
}