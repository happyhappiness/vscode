static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;
  char *ciphers;
  struct SessionHandle *data = conn->data;
  SSL_METHOD_QUAL SSL_METHOD *req_method = NULL;
  void *ssl_sessionid = NULL;
  X509_LOOKUP *lookup = NULL;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  long ctx_options;
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
  bool sni;
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif
#endif
#ifdef HAS_ALPN
  unsigned char protocols[128];
#endif

  DEBUGASSERT(ssl_connect_1 == connssl->connecting_state);

  /* Make funny stuff to get random input */
  Curl_ossl_seed(data);

  data->set.ssl.certverifyresult = !X509_V_OK;

  /* check to see if we've been told to use an explicit SSL/TLS version */

  switch(data->set.ssl.version) {
  default:
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
  case CURL_SSLVERSION_TLSv1_0:
  case CURL_SSLVERSION_TLSv1_1:
  case CURL_SSLVERSION_TLSv1_2:
    /* it will be handled later with the context options */
    req_method = SSLv23_client_method();
    use_sni(TRUE);
    break;
  case CURL_SSLVERSION_SSLv2:
#ifdef OPENSSL_NO_SSL2
    failf(data, "OpenSSL was built without SSLv2 support");
    return CURLE_NOT_BUILT_IN;
#else
#ifdef USE_TLS_SRP
    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP)
      return CURLE_SSL_CONNECT_ERROR;
#endif
    req_method = SSLv2_client_method();
    use_sni(FALSE);
    break;
#endif
  case CURL_SSLVERSION_SSLv3:
#ifdef USE_TLS_SRP
    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP)
      return CURLE_SSL_CONNECT_ERROR;
#endif
    req_method = SSLv3_client_method();
    use_sni(FALSE);
    break;
  }

  if(connssl->ctx)
    SSL_CTX_free(connssl->ctx);
  connssl->ctx = SSL_CTX_new(req_method);

  if(!connssl->ctx) {
    failf(data, "SSL: couldn't create a context: %s",
          ERR_error_string(ERR_peek_error(), NULL));
    return CURLE_OUT_OF_MEMORY;
  }

#ifdef SSL_MODE_RELEASE_BUFFERS
  SSL_CTX_set_mode(connssl->ctx, SSL_MODE_RELEASE_BUFFERS);
#endif

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

     The "-no_ticket" option was introduced in Openssl0.9.8j. It's a flag to
     disable "rfc4507bis session ticket support".  rfc4507bis was later turned
     into the proper RFC5077 it seems: http://tools.ietf.org/html/rfc5077

     The enabled extension concerns the session management. I wonder how often
     libcurl stops a connection and then resumes a TLS session. also, sending
     the session data is some overhead. .I suggest that you just use your
     proposed patch (which explicitly disables TICKET).

     If someone writes an application with libcurl and openssl who wants to
     enable the feature, one can do this in the SSL callback.

     SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG option enabling allowed proper
     interoperability with web server Netscape Enterprise Server 2.0.1 which
     was released back in 1996.

     Due to CVE-2010-4180, option SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG has
     become ineffective as of OpenSSL 0.9.8q and 1.0.0c. In order to mitigate
     CVE-2010-4180 when using previous OpenSSL versions we no longer enable
     this option regardless of OpenSSL version and SSL_OP_ALL definition.

     OpenSSL added a work-around for a SSL 3.0/TLS 1.0 CBC vulnerability
     (http://www.openssl.org/~bodo/tls-cbc.txt). In 0.9.6e they added a bit to
     SSL_OP_ALL that _disables_ that work-around despite the fact that
     SSL_OP_ALL is documented to do "rather harmless" workarounds. In order to
     keep the secure work-around, the SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS bit
     must not be set.
  */

  ctx_options = SSL_OP_ALL;

#ifdef SSL_OP_NO_TICKET
  ctx_options |= SSL_OP_NO_TICKET;
#endif

#ifdef SSL_OP_NO_COMPRESSION
  ctx_options |= SSL_OP_NO_COMPRESSION;
#endif

#ifdef SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG
  /* mitigate CVE-2010-4180 */
  ctx_options &= ~SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG;
#endif

#ifdef SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS
  /* unless the user explicitly ask to allow the protocol vulnerability we
     use the work-around */
  if(!conn->data->set.ssl_enable_beast)
    ctx_options &= ~SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS;
#endif

  switch(data->set.ssl.version) {
  case CURL_SSLVERSION_SSLv3:
#ifdef USE_TLS_SRP
    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
      infof(data, "Set version TLSv1.x for SRP authorisation\n");
    }
#endif
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_TLSv1;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
    break;

  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    break;

  case CURL_SSLVERSION_TLSv1_0:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
    break;

#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
  case CURL_SSLVERSION_TLSv1_1:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
    break;

  case CURL_SSLVERSION_TLSv1_2:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
    ctx_options |= SSL_OP_NO_TLSv1_1;
    break;
#endif

#ifndef OPENSSL_NO_SSL2
  case CURL_SSLVERSION_SSLv2:
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
    break;
#endif

  default:
    failf(data, "Unsupported SSL protocol version");
    return CURLE_SSL_CONNECT_ERROR;
  }

  SSL_CTX_set_options(connssl->ctx, ctx_options);

#ifdef USE_NGHTTP2
  if(data->set.httpversion == CURL_HTTP_VERSION_2_0) {
#ifdef HAS_NPN
    if(data->set.ssl_enable_npn) {
      SSL_CTX_set_next_proto_select_cb(connssl->ctx, select_next_proto_cb,
                                       conn);
    }
#endif

#ifdef HAS_ALPN
    if(data->set.ssl_enable_alpn) {
      protocols[0] = NGHTTP2_PROTO_VERSION_ID_LEN;
      memcpy(&protocols[1], NGHTTP2_PROTO_VERSION_ID,
          NGHTTP2_PROTO_VERSION_ID_LEN);

      protocols[NGHTTP2_PROTO_VERSION_ID_LEN+1] = ALPN_HTTP_1_1_LENGTH;
      memcpy(&protocols[NGHTTP2_PROTO_VERSION_ID_LEN+2], ALPN_HTTP_1_1,
          ALPN_HTTP_1_1_LENGTH);

      /* expects length prefixed preference ordered list of protocols in wire
       * format
       */
      SSL_CTX_set_alpn_protos(connssl->ctx, protocols,
          NGHTTP2_PROTO_VERSION_ID_LEN + ALPN_HTTP_1_1_LENGTH + 2);

      infof(data, "ALPN, offering %s, %s\n", NGHTTP2_PROTO_VERSION_ID,
            ALPN_HTTP_1_1);
      connssl->asked_for_h2 = TRUE;
    }
#endif
  }
#endif

  if(data->set.str[STRING_CERT] || data->set.str[STRING_CERT_TYPE]) {
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

  ciphers = data->set.str[STRING_SSL_CIPHER_LIST];
  if(!ciphers)
    ciphers = (char *)DEFAULT_CIPHER_SELECTION;
  if(!SSL_CTX_set_cipher_list(connssl->ctx, ciphers)) {
    failf(data, "failed setting cipher list: %s", ciphers);
    return CURLE_SSL_CIPHER;
  }

#ifdef USE_TLS_SRP
  if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
    infof(data, "Using TLS-SRP username: %s\n", data->set.ssl.username);

    if(!SSL_CTX_set_srp_username(connssl->ctx, data->set.ssl.username)) {
      failf(data, "Unable to set SRP user name");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
    if(!SSL_CTX_set_srp_password(connssl->ctx,data->set.ssl.password)) {
      failf(data, "failed setting SRP password");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
    if(!data->set.str[STRING_SSL_CIPHER_LIST]) {
      infof(data, "Setting cipher list SRP\n");

      if(!SSL_CTX_set_cipher_list(connssl->ctx, "SRP")) {
        failf(data, "failed setting SRP cipher list");
        return CURLE_SSL_CIPHER;
      }
    }
  }
#endif
  if(data->set.str[STRING_SSL_CAFILE] || data->set.str[STRING_SSL_CAPATH]) {
    /* tell SSL where to find CA certificates that are used to verify
       the servers certificate. */
    if(!SSL_CTX_load_verify_locations(connssl->ctx,
                                       data->set.str[STRING_SSL_CAFILE],
                                       data->set.str[STRING_SSL_CAPATH])) {
      if(data->set.ssl.verifypeer) {
        /* Fail if we insist on successfully verifying the server. */
        failf(data,"error setting certificate verify locations:\n"
              "  CAfile: %s\n  CApath: %s",
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

  if(data->set.str[STRING_SSL_CRLFILE]) {
    /* tell SSL where to find CRL file that is used to check certificate
     * revocation */
    lookup=X509_STORE_add_lookup(SSL_CTX_get_cert_store(connssl->ctx),
                                 X509_LOOKUP_file());
    if(!lookup ||
       (!X509_load_crl_file(lookup,data->set.str[STRING_SSL_CRLFILE],
                            X509_FILETYPE_PEM)) ) {
      failf(data,"error loading CRL file: %s",
            data->set.str[STRING_SSL_CRLFILE]);
      return CURLE_SSL_CRL_BADFILE;
    }
    else {
      /* Everything is fine. */
      infof(data, "successfully load CRL file:\n");
      X509_STORE_set_flags(SSL_CTX_get_cert_store(connssl->ctx),
                           X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
    }
    infof(data,
          "  CRLfile: %s\n", data->set.str[STRING_SSL_CRLFILE] ?
          data->set.str[STRING_SSL_CRLFILE]: "none");
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
    result = (*data->set.ssl.fsslctx)(data, connssl->ctx,
                                      data->set.ssl.fsslctxp);
    if(result) {
      failf(data,"error signaled by ssl ctx callback");
      return result;
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

#if (OPENSSL_VERSION_NUMBER >= 0x0090808fL) && !defined(OPENSSL_NO_TLSEXT) && \
    !defined(OPENSSL_IS_BORINGSSL)
  if(data->set.ssl.verifystatus)
    SSL_set_tlsext_status_type(connssl->handle, TLSEXT_STATUSTYPE_ocsp);
#endif

  SSL_set_connect_state(connssl->handle);

  connssl->server_cert = 0x0;

#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
  if((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
#endif
     sni &&
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
  if(!SSL_set_fd(connssl->handle, (int)sockfd)) {
    failf(data, "SSL: SSL_set_fd failed: %s",
          ERR_error_string(ERR_get_error(),NULL));
    return CURLE_SSL_CONNECT_ERROR;
  }

  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}