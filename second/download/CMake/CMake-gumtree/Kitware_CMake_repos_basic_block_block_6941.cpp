{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_SSL_CONNECT_ERROR;
  PRUint32 timeout;
  long * const certverifyresult = SSL_IS_PROXY() ?
    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
  const char * const pinnedpubkey = SSL_IS_PROXY() ?
              data->set.str[STRING_SSL_PINNEDPUBLICKEY_PROXY] :
              data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG];


  /* check timeout situation */
  const time_t time_left = Curl_timeleft(data, NULL, TRUE);
  if(time_left < 0) {
    failf(data, "timed out before SSL handshake");
    result = CURLE_OPERATION_TIMEDOUT;
    goto error;
  }

  /* Force the handshake now */
  timeout = PR_MillisecondsToInterval((PRUint32) time_left);
  if(SSL_ForceHandshakeWithTimeout(connssl->handle, timeout) != SECSuccess) {
    if(PR_GetError() == PR_WOULD_BLOCK_ERROR)
      /* blocking direction is updated by nss_update_connecting_state() */
      return CURLE_AGAIN;
    else if(*certverifyresult == SSL_ERROR_BAD_CERT_DOMAIN)
      result = CURLE_PEER_FAILED_VERIFICATION;
    else if(*certverifyresult != 0)
      result = CURLE_SSL_CACERT;
    goto error;
  }

  result = display_conn_info(conn, connssl->handle);
  if(result)
    goto error;

  if(SSL_SET_OPTION(issuercert)) {
    SECStatus ret = SECFailure;
    char *nickname = dup_nickname(data, SSL_SET_OPTION(issuercert));
    if(nickname) {
      /* we support only nicknames in case of issuercert for now */
      ret = check_issuer_cert(connssl->handle, nickname);
      free(nickname);
    }

    if(SECFailure == ret) {
      infof(data, "SSL certificate issuer check failed\n");
      result = CURLE_SSL_ISSUER_ERROR;
      goto error;
    }
    else {
      infof(data, "SSL certificate issuer check ok\n");
    }
  }

  result = cmp_peer_pubkey(connssl, pinnedpubkey);
  if(result)
    /* status already printed */
    goto error;

  return CURLE_OK;

error:
  return nss_fail_connect(connssl, data, result);
}