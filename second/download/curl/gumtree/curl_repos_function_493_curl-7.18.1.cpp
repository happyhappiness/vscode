static CURLcode
ossl_connect_step1(struct connectdata *conn,
                   int sockindex)
{
  CURLcode retcode = CURLE_OK;

  struct SessionHandle *data = conn->data;
  SSL_METHOD_QUAL SSL_METHOD *req_method=NULL;
  void *ssl_sessionid=NULL;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif
#endif

  DEBUGASSERT(ssl_connect_1 == connssl->connecting_state);

  /* Make funny stuff to get random input */
  Curl_ossl_seed(data);

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

  if(connssl->ctx)
    SSL_CTX_free(connssl->ctx);
  connssl->ctx = SSL_CTX_new(req_method);

  if(!connssl->ctx) {
    failf(data, "SSL: couldn't create a context!");
    return CURLE_OUT_OF_MEMORY;
  }

#ifdef SSL_CTRL_SET_MSG_CALLBACK
  if(data->set.fdebug && data->set.verbose) {
    /* the SSL trace callback is only used for verbose logging so we only
       inform about failures of setting it */
    if(!SSL_CTX_callback_ctrl(connssl->ctx, SSL_CTRL_SET_MSG_CALLBACK,
                               (void (*)(void))ssl_tls_trace)) {
      infof(data, "SSL: couldn't set callback!\n");
    }
    else if(!SSL_CTX_ctrl(connssl->ctx, SSL_CTRL_SET_MSG_CALLBACK_ARG, 0,
                           conn)) {
      infof(data, "SSL: couldn't set callback argument!\n");
    }
  }
#endif

  /* OpenSSL contains code to work-around lots of bugs and flaws in various
     SSL-implementations. SSL_CTX_set_options() is used to enabled those
     work-arounds. The man page for this option states that SSL_OP_ALL enables
     all the work-arounds and that "It is usually safe to use SSL_OP_ALL to
     enable the bug workaround options if compatibility with somewhat broken
     implementations is desired."

  */
  SSL_CTX_set_options(connssl->ctx, SSL_OP_ALL);

  /* disable SSLv2 in the default case (i.e. allow SSLv3 and TLSv1) */
  if(data->set.ssl.version == CURL_SSLVERSION_DEFAULT)
    SSL_CTX_set_options(connssl->ctx, SSL_OP_NO_SSLv2);

#if 0
  /*
   * Not sure it's needed to tell SSL_connect() that socket is
   * non-blocking. It doesn't seem to care, but just return with
   * SSL_ERROR_WANT_x.
   */
  if(data->state.used_interface == Curl_if_multi)
    SSL_CTX_ctrl(connssl->ctx, BIO_C_SET_NBIO, 1, NULL);
#endif

  if(data->set.str[STRING_CERT]) {
    if(!cert_stuff(conn,
                   connssl->ctx,
                   data->set.str[STRING_CERT],
                   data->set.str[STRING_CERT_TYPE],
                   data->set.str[STRING_KEY],
                   data->set.str[STRING_KEY_TYPE])) {
      /* failf() is already done in cert_stuff() */
      return CURLE_SSL_CERTPROBLEM;
    }
  }

  if(data->set.str[STRING_SSL_CIPHER_LIST]) {
    if(!SSL_CTX_set_cipher_list(connssl->ctx,
                                data->set.str[STRING_SSL_CIPHER_LIST])) {
      failf(data, "failed setting cipher list");
      return CURLE_SSL_CIPHER;
    }
  }

  if(data->set.str[STRING_SSL_CAFILE] || data->set.str[STRING_SSL_CAPATH]) {
    /* tell SSL where to find CA certificates that are used to verify
       the servers certificate. */
    if(!SSL_CTX_load_verify_locations(connssl->ctx,
                                       data->set.str[STRING_SSL_CAFILE],
                                       data->set.str[STRING_SSL_CAPATH])) {
      if(data->set.ssl.verifypeer) {
        /* Fail if we insist on successfully verifying the server. */
        failf(data,"error setting certificate verify locations:\n"
              "  CAfile: %s\n  CApath: %s\n",
              data->set.str[STRING_SSL_CAFILE]?
              data->set.str[STRING_SSL_CAFILE]: "none",
              data->set.str[STRING_SSL_CAPATH]?
              data->set.str[STRING_SSL_CAPATH] : "none");
        return CURLE_SSL_CACERT_BADFILE;
      }
      else {
        /* Just continue with a warning if no strict  certificate verification
           is required. */
        infof(data, "error setting certificate verify locations,"
              " continuing anyway:\n");
      }
    }
    else {
      /* Everything is fine. */
      infof(data, "successfully set certificate verify locations:\n");
    }
    infof(data,
          "  CAfile: %s\n"
          "  CApath: %s\n",
          data->set.str[STRING_SSL_CAFILE] ? data->set.str[STRING_SSL_CAFILE]:
          "none",
          data->set.str[STRING_SSL_CAPATH] ? data->set.str[STRING_SSL_CAPATH]:
          "none");
  }
  /* SSL always tries to verify the peer, this only says whether it should
   * fail to connect if the verification fails, or if it should continue
   * anyway. In the latter case the result of the verification is checked with
   * SSL_get_verify_result() below. */
  SSL_CTX_set_verify(connssl->ctx,
                     data->set.ssl.verifypeer?SSL_VERIFY_PEER:SSL_VERIFY_NONE,
                     cert_verify_callback);

  /* give application a chance to interfere with SSL set up. */
  if(data->set.ssl.fsslctx) {
    retcode = (*data->set.ssl.fsslctx)(data, connssl->ctx,
                                       data->set.ssl.fsslctxp);
    if(retcode) {
      failf(data,"error signaled by ssl ctx callback");
      return retcode;
    }
  }

  /* Lets make an SSL structure */
  if(connssl->handle)
    SSL_free(connssl->handle);
  connssl->handle = SSL_new(connssl->ctx);
  if(!connssl->handle) {
    failf(data, "SSL: couldn't create a context (handle)!");
    return CURLE_OUT_OF_MEMORY;
  }
  SSL_set_connect_state(connssl->handle);

  connssl->server_cert = 0x0;

#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
  if ((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
#ifdef ENABLE_IPV6
      (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
#endif
      !SSL_set_tlsext_host_name(connssl->handle, conn->host.name))
    infof(data, "WARNING: failed to configure server name indication (SNI) "
          "TLS extension\n");
#endif

  /* Check if there's a cached ID we can/should use here! */
  if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL)) {
    /* we got a session id, use it! */
    if(!SSL_set_session(connssl->handle, ssl_sessionid)) {
      failf(data, "SSL: SSL_set_session failed: %s",
            ERR_error_string(ERR_get_error(),NULL));
      return CURLE_SSL_CONNECT_ERROR;
    }
    /* Informational message */
    infof (data, "SSL re-using session ID\n");
  }

  /* pass the raw socket into the SSL layers */
  if(!SSL_set_fd(connssl->handle, sockfd)) {
     failf(data, "SSL: SSL_set_fd failed: %s",
           ERR_error_string(ERR_get_error(),NULL));
     return CURLE_SSL_CONNECT_ERROR;
  }

  connssl->connecting_state = ssl_connect_2;
  return CURLE_OK;
}