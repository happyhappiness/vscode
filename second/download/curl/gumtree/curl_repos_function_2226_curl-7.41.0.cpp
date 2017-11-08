static CURLcode connect_prep(struct connectdata *conn, int sockindex)
{
  struct SessionHandle *data = conn->data;
  SSL_CTX *ssl_ctx;
  SSL *ssl = NULL;
  int cert_types[] = {SSL_OBJ_X509_CERT, SSL_OBJ_PKCS12, 0};
  int key_types[] = {SSL_OBJ_RSA_KEY, SSL_OBJ_PKCS8, SSL_OBJ_PKCS12, 0};
  int i, ssl_fcn_return;
  const uint8_t *ssl_sessionid;
  size_t ssl_idsize;

  /* Assuming users will not compile in custom key/cert to axTLS.
  *  Also, even for blocking connects, use axTLS non-blocking feature.
  */
  uint32_t client_option = SSL_NO_DEFAULT_KEY |
    SSL_SERVER_VERIFY_LATER |
    SSL_CONNECT_IN_PARTS;

  if(conn->ssl[sockindex].state == ssl_connection_complete)
    /* to make us tolerant against being called more than once for the
       same connection */
    return CURLE_OK;

  /* axTLS only supports TLSv1 */
  /* check to see if we've been told to use an explicit SSL/TLS version */
  switch(data->set.ssl.version) {
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

  conn->ssl[sockindex].ssl_ctx = ssl_ctx;
  conn->ssl[sockindex].ssl = NULL;

  /* Load the trusted CA cert bundle file */
  if(data->set.ssl.CAfile) {
    if(ssl_obj_load(ssl_ctx, SSL_OBJ_X509_CACERT, data->set.ssl.CAfile, NULL)
       != SSL_OK) {
      infof(data, "error reading ca cert file %s \n",
            data->set.ssl.CAfile);
      if(data->set.ssl.verifypeer) {
        return CURLE_SSL_CACERT_BADFILE;
      }
    }
    else
      infof(data, "found certificates in %s\n", data->set.ssl.CAfile);
  }

  /* gtls.c tasks we're skipping for now:
   * 1) certificate revocation list checking
   * 2) dns name assignment to host
   * 3) set protocol priority.  axTLS is TLSv1 only, so can probably ignore
   * 4) set certificate priority.  axTLS ignores type and sends certs in
   *  order added.  can probably ignore this.
   */

  /* Load client certificate */
  if(data->set.str[STRING_CERT]) {
    i=0;
    /* Instead of trying to analyze cert type here, let axTLS try them all. */
    while(cert_types[i] != 0) {
      ssl_fcn_return = ssl_obj_load(ssl_ctx, cert_types[i],
                                    data->set.str[STRING_CERT], NULL);
      if(ssl_fcn_return == SSL_OK) {
        infof(data, "successfully read cert file %s \n",
              data->set.str[STRING_CERT]);
        break;
      }
      i++;
    }
    /* Tried all cert types, none worked. */
    if(cert_types[i] == 0) {
      failf(data, "%s is not x509 or pkcs12 format",
            data->set.str[STRING_CERT]);
      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load client key.
     If a pkcs12 file successfully loaded a cert, then there's nothing to do
     because the key has already been loaded. */
  if(data->set.str[STRING_KEY] && cert_types[i] != SSL_OBJ_PKCS12) {
    i=0;
    /* Instead of trying to analyze key type here, let axTLS try them all. */
    while(key_types[i] != 0) {
      ssl_fcn_return = ssl_obj_load(ssl_ctx, key_types[i],
                                    data->set.str[STRING_KEY], NULL);
      if(ssl_fcn_return == SSL_OK) {
        infof(data, "successfully read key file %s \n",
              data->set.str[STRING_KEY]);
        break;
      }
      i++;
    }
    /* Tried all key types, none worked. */
    if(key_types[i] == 0) {
      failf(data, "Failure: %s is not a supported key file",
            data->set.str[STRING_KEY]);
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  /* gtls.c does more here that is being left out for now
   * 1) set session credentials.  can probably ignore since axtls puts this
   *    info in the ssl_ctx struct
   * 2) setting up callbacks.  these seem gnutls specific
   */

  /* In axTLS, handshaking happens inside ssl_client_new. */
  if(!Curl_ssl_getsessionid(conn, (void **) &ssl_sessionid, &ssl_idsize)) {
    /* we got a session id, use it! */
    infof (data, "SSL re-using session ID\n");
    ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex],
                         ssl_sessionid, (uint8_t)ssl_idsize);
  }
  else
    ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex], NULL, 0);

  conn->ssl[sockindex].ssl = ssl;
  return CURLE_OK;
}