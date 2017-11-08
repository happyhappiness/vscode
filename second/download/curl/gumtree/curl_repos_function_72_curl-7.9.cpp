CURLcode
Curl_SSLConnect(struct connectdata *conn)
{
  CURLcode retcode = CURLE_OK;

#ifdef USE_SSLEAY
  struct SessionHandle *data = conn->data;
  int err;
  char * str;
  SSL_METHOD *req_method;
  SSL_SESSION *ssl_sessionid=NULL;
  ASN1_TIME *certdate;

  /* mark this is being ssl enabled from here on out. */
  conn->ssl.use = TRUE;

  /* Make funny stuff to get random input */
  random_the_seed(conn);
    
  switch(data->set.ssl.version) {
  default:
    req_method = SSLv23_client_method();
    break;
  case 2:
    req_method = SSLv2_client_method();
    break;
  case 3:
    req_method = SSLv3_client_method();
    break;
  }
    
  conn->ssl.ctx = SSL_CTX_new(req_method);

  if(!conn->ssl.ctx) {
    failf(data, "SSL: couldn't create a context!");
    return CURLE_OUT_OF_MEMORY;
  }
    
  if(data->set.cert) {
    if (!cert_stuff(conn, data->set.cert, data->set.cert)) {
      /* failf() is already done in cert_stuff() */
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  if(data->set.ssl.cipher_list) {
    if (!SSL_CTX_set_cipher_list(conn->ssl.ctx,
                                 data->set.ssl.cipher_list)) {
      failf(data, "failed setting cipher list\n");
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  if(data->set.ssl.verifypeer){
    SSL_CTX_set_verify(conn->ssl.ctx,
                       SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT|
                       SSL_VERIFY_CLIENT_ONCE,
                       cert_verify_callback);
    if (!SSL_CTX_load_verify_locations(conn->ssl.ctx,
                                       data->set.ssl.CAfile,
                                       data->set.ssl.CApath)) {
      failf(data,"error setting cerficate verify locations\n");
      return CURLE_SSL_CONNECT_ERROR;
    }
  }
  else
    SSL_CTX_set_verify(conn->ssl.ctx, SSL_VERIFY_NONE, cert_verify_callback);


  /* Lets make an SSL structure */
  conn->ssl.handle = SSL_new (conn->ssl.ctx);
  SSL_set_connect_state (conn->ssl.handle);

  conn->ssl.server_cert = 0x0;

  if(!conn->bits.reuse) {
    /* We're not re-using a connection, check if there's a cached ID we
       can/should use here! */
    if(!Get_SSL_Session(conn, &ssl_sessionid)) {
      /* we got a session id, use it! */
      SSL_set_session(conn->ssl.handle, ssl_sessionid);
      /* Informational message */
      infof (data, "SSL re-using session ID\n");
    }
  }

  /* pass the raw socket into the SSL layers */
  SSL_set_fd (conn->ssl.handle, conn->firstsocket);
  err = SSL_connect (conn->ssl.handle);

  /* 1  is fine
     0  is "not successful but was shut down controlled"
     <0 is "handshake was not successful, because a fatal error occurred" */
  if (err <= 0) {
    err = ERR_get_error(); 
    failf(data, "SSL: %s", ERR_error_string(err, NULL));
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* Informational message */
  infof (data, "SSL connection using %s\n",
         SSL_get_cipher(conn->ssl.handle));

  if(!ssl_sessionid) {
    /* Since this is not a cached session ID, then we want to stach this one
       in the cache! */
    Store_SSL_Session(conn);
  }

  
  /* Get server's certificate (note: beware of dynamic allocation) - opt */
  /* major serious hack alert -- we should check certificates
   * to authenticate the server; otherwise we risk man-in-the-middle
   * attack
   */

  conn->ssl.server_cert = SSL_get_peer_certificate (conn->ssl.handle);
  if(!conn->ssl.server_cert) {
    failf(data, "SSL: couldn't get peer certificate!");
    return CURLE_SSL_PEER_CERTIFICATE;
  }
  infof (data, "Server certificate:\n");
  
  str = X509_NAME_oneline (X509_get_subject_name (conn->ssl.server_cert),
                           NULL, 0);
  if(!str) {
    failf(data, "SSL: couldn't get X509-subject!");
    X509_free(conn->ssl.server_cert);
    return CURLE_SSL_CONNECT_ERROR;
  }
  infof(data, "\t subject: %s\n", str);
  CRYPTO_free(str);

  certdate = X509_get_notBefore(conn->ssl.server_cert);
  Curl_ASN1_UTCTIME_output(conn, "\t start date: ", certdate);

  certdate = X509_get_notAfter(conn->ssl.server_cert);
  Curl_ASN1_UTCTIME_output(conn, "\t expire date: ", certdate);

  if (data->set.ssl.verifyhost) {
    char peer_CN[257];
    if (X509_NAME_get_text_by_NID(X509_get_subject_name(conn->ssl.server_cert),
                                  NID_commonName,
                                  peer_CN,
                                  sizeof(peer_CN)) < 0) {
      failf(data, "SSL: unable to obtain common name from peer certificate");
      X509_free(conn->ssl.server_cert);
      return CURLE_SSL_PEER_CERTIFICATE;
    }

    if (!strequal(peer_CN, conn->hostname)) {
      if (data->set.ssl.verifyhost > 1) {
        failf(data, "SSL: certificate subject name '%s' does not match "
              "target host name '%s'",
              peer_CN, conn->hostname);
        X509_free(conn->ssl.server_cert);
        return CURLE_SSL_PEER_CERTIFICATE;
      }
      else
        infof(data,
              "\t common name: %s (does not match '%s')\n",
              peer_CN, conn->hostname);
    }
    else
      infof(data, "\t common name: %s (matched)\n", peer_CN);
  }

  str = X509_NAME_oneline (X509_get_issuer_name  (conn->ssl.server_cert),
                           NULL, 0);
  if(!str) {
    failf(data, "SSL: couldn't get X509-issuer name!");
    X509_free(conn->ssl.server_cert);
    return CURLE_SSL_CONNECT_ERROR;
  }
  infof(data, "\t issuer: %s\n", str);
  CRYPTO_free(str);

  /* We could do all sorts of certificate verification stuff here before
     deallocating the certificate. */

  if(data->set.ssl.verifypeer) {
    data->set.ssl.certverifyresult=SSL_get_verify_result(conn->ssl.handle);
    if (data->set.ssl.certverifyresult != X509_V_OK) {
      failf(data, "SSL certificate verify result: %d\n",
            data->set.ssl.certverifyresult);
      retcode = CURLE_SSL_PEER_CERTIFICATE;
    }
  }
  else
    data->set.ssl.certverifyresult=0;

  X509_free(conn->ssl.server_cert);
#else /* USE_SSLEAY */
  /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
  (void) conn;
#endif
  return retcode;
}