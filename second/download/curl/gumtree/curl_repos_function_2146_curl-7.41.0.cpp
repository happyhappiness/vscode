static CURLcode gskit_connect_step1(struct connectdata *conn, int sockindex)
{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  gsk_handle envir;
  CURLcode result;
  int rc;
  char *keyringfile;
  char *keyringpwd;
  char *keyringlabel;
  char *sni;
  unsigned int protoflags;
  long timeout;
  Qso_OverlappedIO_t commarea;

  /* Create SSL environment, start (preferably asynchronous) handshake. */

  connssl->handle = (gsk_handle) NULL;
  connssl->iocport = -1;

  /* GSKit supports two ways of specifying an SSL context: either by
   *  application identifier (that should have been defined at the system
   *  level) or by keyring file, password and certificate label.
   * Local certificate name (CURLOPT_SSLCERT) is used to hold either the
   *  application identifier of the certificate label.
   * Key password (CURLOPT_KEYPASSWD) holds the keyring password.
   * It is not possible to have different keyrings for the CAs and the
   *  local certificate. We thus use the CA file (CURLOPT_CAINFO) to identify
   *  the keyring file.
   * If no key password is given and the keyring is the system keyring,
   *  application identifier mode is tried first, as recommended in IBM doc.
   */

  keyringfile = data->set.str[STRING_SSL_CAFILE];
  keyringpwd = data->set.str[STRING_KEY_PASSWD];
  keyringlabel = data->set.str[STRING_CERT];
  envir = (gsk_handle) NULL;

  if(keyringlabel && *keyringlabel && !keyringpwd &&
      !strcmp(keyringfile, CURL_CA_BUNDLE)) {
    /* Try application identifier mode. */
    init_environment(data, &envir, keyringlabel, (const char *) NULL,
                     (const char *) NULL, (const char *) NULL);
  }

  if(!envir) {
    /* Use keyring mode. */
    result = init_environment(data, &envir, (const char *) NULL,
                              keyringfile, keyringlabel, keyringpwd);
    if(result)
      return result;
  }

  /* Create secure session. */
  result = gskit_status(data, gsk_secure_soc_open(envir, &connssl->handle),
                        "gsk_secure_soc_open()", CURLE_SSL_CONNECT_ERROR);
  gsk_environment_close(&envir);
  if(result)
    return result;

  /* Determine which SSL/TLS version should be enabled. */
  protoflags = CURL_GSKPROTO_TLSV10_MASK | CURL_GSKPROTO_TLSV11_MASK |
               CURL_GSKPROTO_TLSV12_MASK;
  sni = conn->host.name;
  switch (data->set.ssl.version) {
  case CURL_SSLVERSION_SSLv2:
    protoflags = CURL_GSKPROTO_SSLV2_MASK;
    sni = (char *) NULL;
    break;
  case CURL_SSLVERSION_SSLv3:
    protoflags = CURL_GSKPROTO_SSLV3_MASK;
    sni = (char *) NULL;
    break;
  case CURL_SSLVERSION_TLSv1:
    protoflags = CURL_GSKPROTO_TLSV10_MASK |
                 CURL_GSKPROTO_TLSV11_MASK | CURL_GSKPROTO_TLSV12_MASK;
    break;
  case CURL_SSLVERSION_TLSv1_0:
    protoflags = CURL_GSKPROTO_TLSV10_MASK;
    break;
  case CURL_SSLVERSION_TLSv1_1:
    protoflags = CURL_GSKPROTO_TLSV11_MASK;
    break;
  case CURL_SSLVERSION_TLSv1_2:
    protoflags = CURL_GSKPROTO_TLSV12_MASK;
    break;
  }

  /* Process SNI. Ignore if not supported (on OS400 < V7R1). */
  if(sni) {
    result = set_buffer(data, connssl->handle,
                        GSK_SSL_EXTN_SERVERNAME_REQUEST, sni, TRUE);
    if(result == CURLE_UNSUPPORTED_PROTOCOL)
      result = CURLE_OK;
  }

  /* Set session parameters. */
  if(!result) {
    /* Compute the handshake timeout. Since GSKit granularity is 1 second,
       we round up the required value. */
    timeout = Curl_timeleft(data, NULL, TRUE);
    if(timeout < 0)
      result = CURLE_OPERATION_TIMEDOUT;
    else
      result = set_numeric(data, connssl->handle, GSK_HANDSHAKE_TIMEOUT,
                           (timeout + 999) / 1000);
  }
  if(!result)
    result = set_numeric(data, connssl->handle, GSK_FD, conn->sock[sockindex]);
  if(!result)
    result = set_ciphers(data, connssl->handle, &protoflags);
  if(!protoflags) {
    failf(data, "No SSL protocol/cipher combination enabled");
    result = CURLE_SSL_CIPHER;
  }
  if(!result)
    result = set_enum(data, connssl->handle, GSK_PROTOCOL_SSLV2,
                      (protoflags & CURL_GSKPROTO_SSLV2_MASK)?
                      GSK_PROTOCOL_SSLV2_ON: GSK_PROTOCOL_SSLV2_OFF, FALSE);
  if(!result)
    result = set_enum(data, connssl->handle, GSK_PROTOCOL_SSLV3,
                      (protoflags & CURL_GSKPROTO_SSLV3_MASK)?
                      GSK_PROTOCOL_SSLV3_ON: GSK_PROTOCOL_SSLV3_OFF, FALSE);
  if(!result)
    result = set_enum(data, connssl->handle, GSK_PROTOCOL_TLSV1,
                      (protoflags & CURL_GSKPROTO_TLSV10_MASK)?
                      GSK_PROTOCOL_TLSV1_ON: GSK_PROTOCOL_TLSV1_OFF, FALSE);
  if(!result) {
    result = set_enum(data, connssl->handle, GSK_PROTOCOL_TLSV11,
                      (protoflags & CURL_GSKPROTO_TLSV11_MASK)?
                      GSK_TRUE: GSK_FALSE, TRUE);
    if(result == CURLE_UNSUPPORTED_PROTOCOL) {
      result = CURLE_OK;
      if(protoflags == CURL_GSKPROTO_TLSV11_MASK) {
        failf(data, "TLS 1.1 not yet supported");
        result = CURLE_SSL_CIPHER;
      }
    }
  }
  if(!result) {
    result = set_enum(data, connssl->handle, GSK_PROTOCOL_TLSV12,
                      (protoflags & CURL_GSKPROTO_TLSV12_MASK)?
                      GSK_TRUE: GSK_FALSE, TRUE);
    if(result == CURLE_UNSUPPORTED_PROTOCOL) {
      result = CURLE_OK;
      if(protoflags == CURL_GSKPROTO_TLSV12_MASK) {
        failf(data, "TLS 1.2 not yet supported");
        result = CURLE_SSL_CIPHER;
      }
    }
  }
  if(!result)
    result = set_enum(data, connssl->handle, GSK_SERVER_AUTH_TYPE,
                      data->set.ssl.verifypeer? GSK_SERVER_AUTH_FULL:
                      GSK_SERVER_AUTH_PASSTHRU, FALSE);

  if(!result) {
    /* Start handshake. Try asynchronous first. */
    memset(&commarea, 0, sizeof commarea);
    connssl->iocport = QsoCreateIOCompletionPort();
    if(connssl->iocport != -1) {
      result = gskit_status(data,
                            gsk_secure_soc_startInit(connssl->handle,
                                                     connssl->iocport,
                                                     &commarea),
                            "gsk_secure_soc_startInit()",
                            CURLE_SSL_CONNECT_ERROR);
      if(!result) {
        connssl->connecting_state = ssl_connect_2;
        return CURLE_OK;
      }
      else
        close_async_handshake(connssl);
    }
    else if(errno != ENOBUFS)
      result = gskit_status(data, GSK_ERROR_IO,
                            "QsoCreateIOCompletionPort()", 0);
    else {
      /* No more completion port available. Use synchronous IO. */
      result = gskit_status(data, gsk_secure_soc_init(connssl->handle),
                            "gsk_secure_soc_init()", CURLE_SSL_CONNECT_ERROR);
      if(!result) {
        connssl->connecting_state = ssl_connect_3;
        return CURLE_OK;
      }
    }
  }

  /* Error: rollback. */
  close_one(connssl, data);
  return result;
}