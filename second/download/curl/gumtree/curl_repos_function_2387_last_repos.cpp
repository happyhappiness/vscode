static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;
  char *ciphers;
  struct Curl_easy *data = conn->data;
  SSL_METHOD_QUAL SSL_METHOD *req_method = NULL;
  X509_LOOKUP *lookup = NULL;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  long ctx_options = 0;
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
  bool sni;
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif
#endif
  long * const certverifyresult = SSL_IS_PROXY() ?
    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
  const long int ssl_version = SSL_CONN_CONFIG(version);
#ifdef USE_TLS_SRP
  const enum CURL_TLSAUTH ssl_authtype = SSL_SET_OPTION(authtype);
#endif
  char * const ssl_cert = SSL_SET_OPTION(cert);
  const char * const ssl_cert_type = SSL_SET_OPTION(cert_type);
  const char * const ssl_cafile = SSL_CONN_CONFIG(CAfile);
  const char * const ssl_capath = SSL_CONN_CONFIG(CApath);
  const bool verifypeer = SSL_CONN_CONFIG(verifypeer);
  const char * const ssl_crlfile = SSL_SET_OPTION(CRLfile);
  char error_buffer[256];

  DEBUGASSERT(ssl_connect_1 == connssl->connecting_state);

  /* Make funny stuff to get random input */
  result = Curl_ossl_seed(data);
  if(result)
    return result;

  *certverifyresult = !X509_V_OK;

  /* check to see if we've been told to use an explicit SSL/TLS version */

  switch(ssl_version) {
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
  case CURL_SSLVERSION_TLSv1_0:
  case CURL_SSLVERSION_TLSv1_1:
  case CURL_SSLVERSION_TLSv1_2:
  case CURL_SSLVERSION_TLSv1_3:
    /* it will be handled later with the context options */
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && \
    !defined(LIBRESSL_VERSION_NUMBER)
    req_method = TLS_client_method();
#else
    req_method = SSLv23_client_method();
#endif
    use_sni(TRUE);
    break;
  case CURL_SSLVERSION_SSLv2:
#ifdef OPENSSL_NO_SSL2
    failf(data, OSSL_PACKAGE " was built without SSLv2 support");
    return CURLE_NOT_BUILT_IN;
#else
#ifdef USE_TLS_SRP
    if(ssl_authtype == CURL_TLSAUTH_SRP)
      return CURLE_SSL_CONNECT_ERROR;
#endif
    req_method = SSLv2_client_method();
    use_sni(FALSE);
    break;
#endif
  case CURL_SSLVERSION_SSLv3:
#ifdef OPENSSL_NO_SSL3_METHOD
    failf(data, OSSL_PACKAGE " was built without SSLv3 support");
    return CURLE_NOT_BUILT_IN;
#else
#ifdef USE_TLS_SRP
    if(ssl_authtype == CURL_TLSAUTH_SRP)
      return CURLE_SSL_CONNECT_ERROR;
#endif
    req_method = SSLv3_client_method();
    use_sni(FALSE);
    break;
#endif
  default:
    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
    return CURLE_SSL_CONNECT_ERROR;
  }

  if(BACKEND->ctx)
    SSL_CTX_free(BACKEND->ctx);
  BACKEND->ctx = SSL_CTX_new(req_method);

  if(!BACKEND->ctx) {
    failf(data, "SSL: couldn't create a context: %s",
          ossl_strerror(ERR_peek_error(), error_buffer, sizeof(error_buffer)));
    return CURLE_OUT_OF_MEMORY;
  }

#ifdef SSL_MODE_RELEASE_BUFFERS
  SSL_CTX_set_mode(BACKEND->ctx, SSL_MODE_RELEASE_BUFFERS);
#endif

#ifdef SSL_CTRL_SET_MSG_CALLBACK
  if(data->set.fdebug && data->set.verbose) {
    /* the SSL trace callback is only used for verbose logging */
    SSL_CTX_set_msg_callback(BACKEND->ctx, ssl_tls_trace);
    SSL_CTX_set_msg_callback_arg(BACKEND->ctx, conn);
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
     into the proper RFC5077 it seems: https://tools.ietf.org/html/rfc5077

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
     (https://www.openssl.org/~bodo/tls-cbc.txt). In 0.9.6e they added a bit to
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
  if(!SSL_SET_OPTION(enable_beast))
    ctx_options &= ~SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS;
#endif

  switch(ssl_version) {
  case CURL_SSLVERSION_SSLv3:
#ifdef USE_TLS_SRP
    if(ssl_authtype == CURL_TLSAUTH_SRP) {
      infof(data, "Set version TLSv1.x for SRP authorisation\n");
    }
#endif
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_TLSv1;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#ifdef TLS1_3_VERSION
    ctx_options |= SSL_OP_NO_TLSv1_3;
#endif
#endif
    break;

  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    break;

  case CURL_SSLVERSION_TLSv1_0:
  case CURL_SSLVERSION_TLSv1_1:
  case CURL_SSLVERSION_TLSv1_2:
  case CURL_SSLVERSION_TLSv1_3:
    result = set_ssl_version_min_max(&ctx_options, conn, sockindex);
    if(result != CURLE_OK)
       return result;
    break;

  case CURL_SSLVERSION_SSLv2:
#ifndef OPENSSL_NO_SSL2
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#ifdef TLS1_3_VERSION
    ctx_options |= SSL_OP_NO_TLSv1_3;
#endif
#endif
    break;
#else
    failf(data, OSSL_PACKAGE " was built without SSLv2 support");
    return CURLE_NOT_BUILT_IN;
#endif

  default:
    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
    return CURLE_SSL_CONNECT_ERROR;
  }

  SSL_CTX_set_options(BACKEND->ctx, ctx_options);

#ifdef HAS_NPN
  if(conn->bits.tls_enable_npn)
    SSL_CTX_set_next_proto_select_cb(BACKEND->ctx, select_next_proto_cb, conn);
#endif

#ifdef HAS_ALPN
  if(conn->bits.tls_enable_alpn) {
    int cur = 0;
    unsigned char protocols[128];

#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2 &&
       (!SSL_IS_PROXY() || !conn->bits.tunnel_proxy)) {
      protocols[cur++] = NGHTTP2_PROTO_VERSION_ID_LEN;

      memcpy(&protocols[cur], NGHTTP2_PROTO_VERSION_ID,
          NGHTTP2_PROTO_VERSION_ID_LEN);
      cur += NGHTTP2_PROTO_VERSION_ID_LEN;
      infof(data, "ALPN, offering %s\n", NGHTTP2_PROTO_VERSION_ID);
    }
#endif

    protocols[cur++] = ALPN_HTTP_1_1_LENGTH;
    memcpy(&protocols[cur], ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH);
    cur += ALPN_HTTP_1_1_LENGTH;
    infof(data, "ALPN, offering %s\n", ALPN_HTTP_1_1);

    /* expects length prefixed preference ordered list of protocols in wire
     * format
     */
    SSL_CTX_set_alpn_protos(BACKEND->ctx, protocols, cur);
  }
#endif

  if(ssl_cert || ssl_cert_type) {
    if(!cert_stuff(conn, BACKEND->ctx, ssl_cert, ssl_cert_type,
                   SSL_SET_OPTION(key), SSL_SET_OPTION(key_type),
                   SSL_SET_OPTION(key_passwd))) {
      /* failf() is already done in cert_stuff() */
      return CURLE_SSL_CERTPROBLEM;
    }
  }

  ciphers = SSL_CONN_CONFIG(cipher_list);
  if(!ciphers)
    ciphers = (char *)DEFAULT_CIPHER_SELECTION;
  if(ciphers) {
    if(!SSL_CTX_set_cipher_list(BACKEND->ctx, ciphers)) {
      failf(data, "failed setting cipher list: %s", ciphers);
      return CURLE_SSL_CIPHER;
    }
    infof(data, "Cipher selection: %s\n", ciphers);
  }

#ifdef USE_TLS_SRP
  if(ssl_authtype == CURL_TLSAUTH_SRP) {
    char * const ssl_username = SSL_SET_OPTION(username);

    infof(data, "Using TLS-SRP username: %s\n", ssl_username);

    if(!SSL_CTX_set_srp_username(BACKEND->ctx, ssl_username)) {
      failf(data, "Unable to set SRP user name");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
    if(!SSL_CTX_set_srp_password(BACKEND->ctx, SSL_SET_OPTION(password))) {
      failf(data, "failed setting SRP password");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
    if(!SSL_CONN_CONFIG(cipher_list)) {
      infof(data, "Setting cipher list SRP\n");

      if(!SSL_CTX_set_cipher_list(BACKEND->ctx, "SRP")) {
        failf(data, "failed setting SRP cipher list");
        return CURLE_SSL_CIPHER;
      }
    }
  }
#endif

  if(ssl_cafile || ssl_capath) {
    /* tell SSL where to find CA certificates that are used to verify
       the servers certificate. */
    if(!SSL_CTX_load_verify_locations(BACKEND->ctx, ssl_cafile, ssl_capath)) {
      if(verifypeer) {
        /* Fail if we insist on successfully verifying the server. */
        failf(data, "error setting certificate verify locations:\n"
              "  CAfile: %s\n  CApath: %s",
              ssl_cafile ? ssl_cafile : "none",
              ssl_capath ? ssl_capath : "none");
        return CURLE_SSL_CACERT_BADFILE;
      }
      /* Just continue with a warning if no strict  certificate verification
         is required. */
      infof(data, "error setting certificate verify locations,"
            " continuing anyway:\n");
    }
    else {
      /* Everything is fine. */
      infof(data, "successfully set certificate verify locations:\n");
    }
    infof(data,
          "  CAfile: %s\n"
          "  CApath: %s\n",
          ssl_cafile ? ssl_cafile : "none",
          ssl_capath ? ssl_capath : "none");
  }
#ifdef CURL_CA_FALLBACK
  else if(verifypeer) {
    /* verfying the peer without any CA certificates won't
       work so use openssl's built in default as fallback */
    SSL_CTX_set_default_verify_paths(BACKEND->ctx);
  }
#endif

  if(ssl_crlfile) {
    /* tell SSL where to find CRL file that is used to check certificate
     * revocation */
    lookup = X509_STORE_add_lookup(SSL_CTX_get_cert_store(BACKEND->ctx),
                                 X509_LOOKUP_file());
    if(!lookup ||
       (!X509_load_crl_file(lookup, ssl_crlfile, X509_FILETYPE_PEM)) ) {
      failf(data, "error loading CRL file: %s", ssl_crlfile);
      return CURLE_SSL_CRL_BADFILE;
    }
    /* Everything is fine. */
    infof(data, "successfully load CRL file:\n");
    X509_STORE_set_flags(SSL_CTX_get_cert_store(BACKEND->ctx),
                         X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);

    infof(data, "  CRLfile: %s\n", ssl_crlfile);
  }

  /* Try building a chain using issuers in the trusted store first to avoid
  problems with server-sent legacy intermediates.
  Newer versions of OpenSSL do alternate chain checking by default which
  gives us the same fix without as much of a performance hit (slight), so we
  prefer that if available.
  https://rt.openssl.org/Ticket/Display.html?id=3621&user=guest&pass=guest
  */
#if defined(X509_V_FLAG_TRUSTED_FIRST) && !defined(X509_V_FLAG_NO_ALT_CHAINS)
  if(verifypeer) {
    X509_STORE_set_flags(SSL_CTX_get_cert_store(BACKEND->ctx),
                         X509_V_FLAG_TRUSTED_FIRST);
  }
#endif

  /* SSL always tries to verify the peer, this only says whether it should
   * fail to connect if the verification fails, or if it should continue
   * anyway. In the latter case the result of the verification is checked with
   * SSL_get_verify_result() below. */
  SSL_CTX_set_verify(BACKEND->ctx,
                     verifypeer ? SSL_VERIFY_PEER : SSL_VERIFY_NONE, NULL);

  /* Enable logging of secrets to the file specified in env SSLKEYLOGFILE. */
#if defined(ENABLE_SSLKEYLOGFILE) && defined(HAVE_KEYLOG_CALLBACK)
  if(keylog_file) {
    SSL_CTX_set_keylog_callback(connssl->ctx, ossl_keylog_callback);
  }
#endif

  /* give application a chance to interfere with SSL set up. */
  if(data->set.ssl.fsslctx) {
    result = (*data->set.ssl.fsslctx)(data, BACKEND->ctx,
                                      data->set.ssl.fsslctxp);
    if(result) {
      failf(data, "error signaled by ssl ctx callback");
      return result;
    }
  }

  /* Lets make an SSL structure */
  if(BACKEND->handle)
    SSL_free(BACKEND->handle);
  BACKEND->handle = SSL_new(BACKEND->ctx);
  if(!BACKEND->handle) {
    failf(data, "SSL: couldn't create a context (handle)!");
    return CURLE_OUT_OF_MEMORY;
  }

#if (OPENSSL_VERSION_NUMBER >= 0x0090808fL) && !defined(OPENSSL_NO_TLSEXT) && \
    !defined(OPENSSL_NO_OCSP)
  if(SSL_CONN_CONFIG(verifystatus))
    SSL_set_tlsext_status_type(BACKEND->handle, TLSEXT_STATUSTYPE_ocsp);
#endif

  SSL_set_connect_state(BACKEND->handle);

  BACKEND->server_cert = 0x0;
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
  if((0 == Curl_inet_pton(AF_INET, hostname, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, hostname, &addr)) &&
#endif
     sni &&
     !SSL_set_tlsext_host_name(BACKEND->handle, hostname))
    infof(data, "WARNING: failed to configure server name indication (SNI) "
          "TLS extension\n");
#endif

  /* Check if there's a cached ID we can/should use here! */
  if(SSL_SET_OPTION(primary.sessionid)) {
    void *ssl_sessionid = NULL;

    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL, sockindex)) {
      /* we got a session id, use it! */
      if(!SSL_set_session(BACKEND->handle, ssl_sessionid)) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "SSL: SSL_set_session failed: %s",
              ossl_strerror(ERR_get_error(), error_buffer,
                            sizeof(error_buffer)));
        return CURLE_SSL_CONNECT_ERROR;
      }
      /* Informational message */
      infof(data, "SSL re-using session ID\n");
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  if(conn->proxy_ssl[sockindex].use) {
    BIO *const bio = BIO_new(BIO_f_ssl());
    SSL *handle = conn->proxy_ssl[sockindex].backend->handle;
    DEBUGASSERT(ssl_connection_complete == conn->proxy_ssl[sockindex].state);
    DEBUGASSERT(handle != NULL);
    DEBUGASSERT(bio != NULL);
    BIO_set_ssl(bio, handle, FALSE);
    SSL_set_bio(BACKEND->handle, bio, bio);
  }
  else if(!SSL_set_fd(BACKEND->handle, (int)sockfd)) {
    /* pass the raw socket into the SSL layers */
    failf(data, "SSL: SSL_set_fd failed: %s",
          ossl_strerror(ERR_get_error(), error_buffer, sizeof(error_buffer)));
    return CURLE_SSL_CONNECT_ERROR;
  }

  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}