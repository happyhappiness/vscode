{
  PRFileDesc *model = NULL;
  PRFileDesc *nspr_io = NULL;
  PRFileDesc *nspr_io_stub = NULL;
  PRBool ssl_no_cache;
  PRBool ssl_cbc_random_iv;
  struct Curl_easy *data = conn->data;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CURLcode result;
  bool second_layer = FALSE;

  SSLVersionRange sslver = {
    SSL_LIBRARY_VERSION_TLS_1_0,  /* min */
    SSL_LIBRARY_VERSION_TLS_1_0   /* max */
  };

  connssl->data = data;

  /* list of all NSS objects we need to destroy in Curl_nss_close() */
  Curl_llist_init(&connssl->obj_list, nss_destroy_object);

  /* FIXME. NSS doesn't support multiple databases open at the same time. */
  PR_Lock(nss_initlock);
  result = nss_init(conn->data);
  if(result) {
    PR_Unlock(nss_initlock);
    goto error;
  }

  PK11_SetPasswordFunc(nss_get_password);

  result = nss_load_module(&pem_module, pem_library, "PEM");
  PR_Unlock(nss_initlock);
  if(result == CURLE_FAILED_INIT)
    infof(data, "WARNING: failed to load NSS PEM library %s. Using "
                "OpenSSL PEM certificates will not work.\n", pem_library);
  else if(result)
    goto error;

  result = CURLE_SSL_CONNECT_ERROR;

  model = PR_NewTCPSocket();
  if(!model)
    goto error;
  model = SSL_ImportFD(NULL, model);

  if(SSL_OptionSet(model, SSL_SECURITY, PR_TRUE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_SERVER, PR_FALSE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_CLIENT, PR_TRUE) != SECSuccess)
    goto error;

  /* do not use SSL cache if disabled or we are not going to verify peer */
  ssl_no_cache = (SSL_SET_OPTION(primary.sessionid)
                  && SSL_CONN_CONFIG(verifypeer)) ? PR_FALSE : PR_TRUE;
  if(SSL_OptionSet(model, SSL_NO_CACHE, ssl_no_cache) != SECSuccess)
    goto error;

  /* enable/disable the requested SSL version(s) */
  if(nss_init_sslver(&sslver, data, conn) != CURLE_OK)
    goto error;
  if(SSL_VersionRangeSet(model, &sslver) != SECSuccess)
    goto error;

  ssl_cbc_random_iv = !SSL_SET_OPTION(enable_beast);
#ifdef SSL_CBC_RANDOM_IV
  /* unless the user explicitly asks to allow the protocol vulnerability, we
     use the work-around */
  if(SSL_OptionSet(model, SSL_CBC_RANDOM_IV, ssl_cbc_random_iv) != SECSuccess)
    infof(data, "warning: failed to set SSL_CBC_RANDOM_IV = %d\n",
          ssl_cbc_random_iv);
#else
  if(ssl_cbc_random_iv)
    infof(data, "warning: support for SSL_CBC_RANDOM_IV not compiled in\n");
#endif

  if(SSL_CONN_CONFIG(cipher_list)) {
    if(set_ciphers(data, model, SSL_CONN_CONFIG(cipher_list)) != SECSuccess) {
      result = CURLE_SSL_CIPHER;
      goto error;
    }
  }

  if(!SSL_CONN_CONFIG(verifypeer) && SSL_CONN_CONFIG(verifyhost))
    infof(data, "warning: ignoring value of ssl.verifyhost\n");

  /* bypass the default SSL_AuthCertificate() hook in case we do not want to
   * verify peer */
  if(SSL_AuthCertificateHook(model, nss_auth_cert_hook, conn) != SECSuccess)
    goto error;

  /* not checked yet */
  if(SSL_IS_PROXY())
    data->set.proxy_ssl.certverifyresult = 0;
  else
    data->set.ssl.certverifyresult = 0;

  if(SSL_BadCertHook(model, BadCertHandler, conn) != SECSuccess)
    goto error;

  if(SSL_HandshakeCallback(model, HandshakeCallback, conn) != SECSuccess)
    goto error;

  {
    const CURLcode rv = nss_load_ca_certificates(conn, sockindex);
    if((rv == CURLE_SSL_CACERT_BADFILE) && !SSL_CONN_CONFIG(verifypeer))
      /* not a fatal error because we are not going to verify the peer */
      infof(data, "warning: CA certificates failed to load\n");
    else if(rv) {
      result = rv;
      goto error;
    }
  }

  if(SSL_SET_OPTION(CRLfile)) {
    const CURLcode rv = nss_load_crl(SSL_SET_OPTION(CRLfile));
    if(rv) {
      result = rv;
      goto error;
    }
    infof(data, "  CRLfile: %s\n", SSL_SET_OPTION(CRLfile));
  }

  if(SSL_SET_OPTION(cert)) {
    char *nickname = dup_nickname(data, SSL_SET_OPTION(cert));
    if(nickname) {
      /* we are not going to use libnsspem.so to read the client cert */
      connssl->obj_clicert = NULL;
    }
    else {
      CURLcode rv = cert_stuff(conn, sockindex, SSL_SET_OPTION(cert),
                               SSL_SET_OPTION(key));
      if(rv) {
        /* failf() is already done in cert_stuff() */
        result = rv;
        goto error;
      }
    }

    /* store the nickname for SelectClientCert() called during handshake */
    connssl->client_nickname = nickname;
  }
  else
    connssl->client_nickname = NULL;

  if(SSL_GetClientAuthDataHook(model, SelectClientCert,
                               (void *)connssl) != SECSuccess) {
    result = CURLE_SSL_CERTPROBLEM;
    goto error;
  }

  if(conn->proxy_ssl[sockindex].use) {
    DEBUGASSERT(ssl_connection_complete == conn->proxy_ssl[sockindex].state);
    DEBUGASSERT(conn->proxy_ssl[sockindex].handle != NULL);
    nspr_io = conn->proxy_ssl[sockindex].handle;
    second_layer = TRUE;
  }
  else {
    /* wrap OS file descriptor by NSPR's file descriptor abstraction */
    nspr_io = PR_ImportTCPSocket(sockfd);
    if(!nspr_io)
      goto error;
  }

  /* create our own NSPR I/O layer */
  nspr_io_stub = PR_CreateIOLayerStub(nspr_io_identity, &nspr_io_methods);
  if(!nspr_io_stub) {
    if(!second_layer)
      PR_Close(nspr_io);
    goto error;
  }

  /* make the per-connection data accessible from NSPR I/O callbacks */
  nspr_io_stub->secret = (void *)connssl;

  /* push our new layer to the NSPR I/O stack */
  if(PR_PushIOLayer(nspr_io, PR_TOP_IO_LAYER, nspr_io_stub) != PR_SUCCESS) {
    if(!second_layer)
      PR_Close(nspr_io);
    PR_Close(nspr_io_stub);
    goto error;
  }

  /* import our model socket onto the current I/O stack */
  connssl->handle = SSL_ImportFD(model, nspr_io);
  if(!connssl->handle) {
    if(!second_layer)
      PR_Close(nspr_io);
    goto error;
  }

  PR_Close(model); /* We don't need this any more */
  model = NULL;

  /* This is the password associated with the cert that we're using */
  if(SSL_SET_OPTION(key_passwd)) {
    SSL_SetPKCS11PinArg(connssl->handle, SSL_SET_OPTION(key_passwd));
  }

#ifdef SSL_ENABLE_OCSP_STAPLING
  if(SSL_CONN_CONFIG(verifystatus)) {
    if(SSL_OptionSet(connssl->handle, SSL_ENABLE_OCSP_STAPLING, PR_TRUE)
        != SECSuccess)
      goto error;
  }
#endif

#ifdef SSL_ENABLE_NPN
  if(SSL_OptionSet(connssl->handle, SSL_ENABLE_NPN, conn->bits.tls_enable_npn
                   ? PR_TRUE : PR_FALSE) != SECSuccess)
    goto error;
#endif

#ifdef SSL_ENABLE_ALPN
  if(SSL_OptionSet(connssl->handle, SSL_ENABLE_ALPN, conn->bits.tls_enable_alpn
                   ? PR_TRUE : PR_FALSE) != SECSuccess)
    goto error;
#endif

#if NSSVERNUM >= 0x030f04 /* 3.15.4 */
  if(data->set.ssl.falsestart) {
    if(SSL_OptionSet(connssl->handle, SSL_ENABLE_FALSE_START, PR_TRUE)
        != SECSuccess)
      goto error;

    if(SSL_SetCanFalseStartCallback(connssl->handle, CanFalseStartCallback,
        conn) != SECSuccess)
      goto error;
  }
#endif

#if defined(SSL_ENABLE_NPN) || defined(SSL_ENABLE_ALPN)
  if(conn->bits.tls_enable_npn || conn->bits.tls_enable_alpn) {
    int cur = 0;
    unsigned char protocols[128];

#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2) {
      protocols[cur++] = NGHTTP2_PROTO_VERSION_ID_LEN;
      memcpy(&protocols[cur], NGHTTP2_PROTO_VERSION_ID,
          NGHTTP2_PROTO_VERSION_ID_LEN);
      cur += NGHTTP2_PROTO_VERSION_ID_LEN;
    }
#endif
    protocols[cur++] = ALPN_HTTP_1_1_LENGTH;
    memcpy(&protocols[cur], ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH);
    cur += ALPN_HTTP_1_1_LENGTH;

    if(SSL_SetNextProtoNego(connssl->handle, protocols, cur) != SECSuccess)
      goto error;
  }
#endif


  /* Force handshake on next I/O */
  if(SSL_ResetHandshake(connssl->handle, /* asServer */ PR_FALSE)
      != SECSuccess)
    goto error;

  /* propagate hostname to the TLS layer */
  if(SSL_SetURL(connssl->handle, SSL_IS_PROXY() ? conn->http_proxy.host.name :
                conn->host.name) != SECSuccess)
    goto error;

  /* prevent NSS from re-using the session for a different hostname */
  if(SSL_SetSockPeerID(connssl->handle, SSL_IS_PROXY() ?
                       conn->http_proxy.host.name : conn->host.name)
     != SECSuccess)
    goto error;

  return CURLE_OK;

error:
  if(model)
    PR_Close(model);

  return nss_fail_connect(connssl, data, result);
}