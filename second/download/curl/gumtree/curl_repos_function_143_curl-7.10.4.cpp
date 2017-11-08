CURLcode
Curl_SSLConnect(struct connectdata *conn)
{
  CURLcode retcode = CURLE_OK;

#ifdef USE_SSLEAY
  struct SessionHandle *data = conn->data;
  int err;
  int what;
  char * str;
  SSL_METHOD *req_method;
  SSL_SESSION *ssl_sessionid=NULL;
  ASN1_TIME *certdate;

  /* mark this is being ssl enabled from here on out. */
  conn->ssl.use = TRUE;

  if(!ssl_seeded || data->set.ssl.random_file || data->set.ssl.egdsocket) {
    /* Make funny stuff to get random input */
    random_the_seed(data);

    ssl_seeded = TRUE;
  }

  /* check to see if we've been told to use an explicit SSL/TLS version */
  switch(data->set.ssl.version) {
  default:
  case CURL_SSLVERSION_DEFAULT:
    /* we try to figure out version */
    req_method = SSLv23_client_method();
    break;
  case CURL_SSLVERSION_TLSv1:
    req_method = TLSv1_client_method();
    break;
  case CURL_SSLVERSION_SSLv2:
    req_method = SSLv2_client_method();
    break;
  case CURL_SSLVERSION_SSLv3:
    req_method = SSLv3_client_method();
    break;
  }
    
  conn->ssl.ctx = SSL_CTX_new(req_method);

  if(!conn->ssl.ctx) {
    failf(data, "SSL: couldn't create a context!");
    return CURLE_OUT_OF_MEMORY;
  }
    
  if(data->set.cert) {
    if (!cert_stuff(conn,
                    data->set.cert,
                    data->set.cert_type,
                    data->set.key,
                    data->set.key_type)) {
      /* failf() is already done in cert_stuff() */
      return CURLE_SSL_CERTPROBLEM;
    }
  }

  if(data->set.ssl.cipher_list) {
    if (!SSL_CTX_set_cipher_list(conn->ssl.ctx,
                                 data->set.ssl.cipher_list)) {
      failf(data, "failed setting cipher list");
      return CURLE_SSL_CIPHER;
    }
  }

  if(data->set.ssl.verifypeer){
    SSL_CTX_set_verify(conn->ssl.ctx,
                       SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT|
                       SSL_VERIFY_CLIENT_ONCE,
                       cert_verify_callback);
    if ((data->set.ssl.CAfile || data->set.ssl.CApath) &&
        !SSL_CTX_load_verify_locations(conn->ssl.ctx,
                                       data->set.ssl.CAfile,
                                       data->set.ssl.CApath)) {
      failf(data,"error setting certificate verify locations");
      return CURLE_SSL_CACERT;
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
  SSL_set_fd(conn->ssl.handle, conn->firstsocket);

  do {
    fd_set writefd;
    fd_set readfd;
    struct timeval interval;
    long timeout_ms;

    /* Find out if any timeout is set. If not, use 300 seconds.
       Otherwise, figure out the most strict timeout of the two possible one
       and then how much time that has elapsed to know how much time we
       allow for the connect call */
    if(data->set.timeout || data->set.connecttimeout) {
      double has_passed;

      /* Evaluate in milliseconds how much time that has passed */
      has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.start);

#ifndef min
#define min(a, b)   ((a) < (b) ? (a) : (b))
#endif

      /* get the most strict timeout of the ones converted to milliseconds */
      if(data->set.timeout &&
         (data->set.timeout>data->set.connecttimeout))
        timeout_ms = data->set.timeout*1000;
      else
        timeout_ms = data->set.connecttimeout*1000;
      
      /* subtract the passed time */
      timeout_ms -= (long)has_passed;
      
      if(timeout_ms < 0) {
        /* a precaution, no need to continue if time already is up */
        failf(data, "SSL connection timeout");
        return CURLE_OPERATION_TIMEOUTED;
      }
    }
    else
      /* no particular time-out has been set */
      timeout_ms=300000; /* milliseconds, default to five minutes */


    FD_ZERO(&writefd);
    FD_ZERO(&readfd);

    err = SSL_connect(conn->ssl.handle);

    /* 1  is fine
       0  is "not successful but was shut down controlled"
       <0 is "handshake was not successful, because a fatal error occurred" */
    if(1 != err) {
      int detail = SSL_get_error(conn->ssl.handle, err);

      if(SSL_ERROR_WANT_READ == detail)
        FD_SET(conn->firstsocket, &readfd);
      else if(SSL_ERROR_WANT_WRITE == detail)
        FD_SET(conn->firstsocket, &writefd);
      else {
        /* untreated error */
        char error_buffer[120]; /* OpenSSL documents that this must be at least
                                   120 bytes long. */
        /* detail is already set to the SSL error above */
        failf(data, "SSL: %s", ERR_error_string(detail, error_buffer));

        /* OpenSSL 0.9.6 and later has a function named
           ERRO_error_string_n() that takes the size of the buffer as a third
           argument, and we should possibly switch to using that one in the
           future. */
        return CURLE_SSL_CONNECT_ERROR;
      }
    }
    else
      /* we have been connected fine, get out of the connect loop */
      break;

    interval.tv_sec = timeout_ms/1000;
    timeout_ms -= interval.tv_sec*1000;

    interval.tv_usec = timeout_ms*1000;

    what = select(conn->firstsocket+1, &readfd, &writefd, NULL, &interval);
    if(what > 0)
      /* reabable or writable, go loop yourself */
      continue;
    else if(0 == what) {
      /* timeout */
      failf(data, "SSL connection timeout");
      return CURLE_OPERATION_TIMEOUTED;
    }
    else
      break; /* get out of loop */
  } while(1);

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

    if (!cert_hostcheck(peer_CN, conn->hostname)) {
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
      failf(data, "SSL certificate verify result: %d",
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